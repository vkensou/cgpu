#include "oval_device.h"

#include "cgpu/api.h"
#include <SDL.h>
#include <SDL_syswm.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>

struct FrameData
{
	CGPUFenceId inflightFence;
	CGPUCommandPoolId pool;
	std::vector<CGPUCommandBufferId> cmds;
	std::vector<CGPUCommandBufferId> allocated_cmds;
	std::vector<CGPUBufferId> vertex_buffers;

	void newFrame()
	{
		cgpu_reset_command_pool(pool);

		for (auto cmd : allocated_cmds)
			cmds.push_back(cmd);
		allocated_cmds.clear();

		for (auto buffer : vertex_buffers)
			cgpu_free_buffer(buffer);
		vertex_buffers.clear();
	}

	CGPUCommandBufferId request()
	{
		CGPUCommandBufferId cmd;
		if (!cmds.empty())
		{
			cmd = cmds.back();
			cmds.pop_back();
		}
		else
		{
			CGPUCommandBufferDescriptor cmd_desc = { .is_secondary = false };
			cmd = cgpu_create_command_buffer(pool, &cmd_desc);
		}

		allocated_cmds.push_back(cmd);
		return cmd;
	}

	void free()
	{
		cgpu_free_fence(inflightFence);
		inflightFence = CGPU_NULLPTR;

		for (auto cmd : cmds)
			cgpu_free_command_buffer(cmd);
		cmds.clear();

		for (auto cmd : allocated_cmds)
			cgpu_free_command_buffer(cmd);
		allocated_cmds.clear();

		cgpu_free_command_pool(pool);
		pool = CGPU_NULLPTR;

		for (auto buffer : vertex_buffers)
			cgpu_free_buffer(buffer);
		vertex_buffers.clear();
	}
};

struct FrameInfo
{
	CGPUCommandBufferId cmd;
	CGPURenderPassEncoderId rp_encoder;
	uint16_t current_swapchain_index;
	bool prepared;

	void reset()
	{
		prepared = false;
		cmd = CGPU_NULLPTR;
		rp_encoder = CGPU_NULLPTR;
		current_swapchain_index = -1;
	}
};

typedef struct oval_cgpu_device_t {
	oval_device_t super;
	SDL_Window* window;
	CGPUInstanceId instance;
	CGPUDeviceId device;
	CGPUQueueId gfx_queue;
	CGPUQueueId present_queue;
	CGPURenderPassId render_pass;
	CGPUSurfaceId surface;
	CGPUSwapChainId swapchain;
	CGPUTextureViewId swapchain_views[3];
	CGPUFramebufferId swapchain_framebuffer[3];
	CGPUSemaphoreId swapchain_prepared_semaphores[3];
	FrameData frameDatas[3];
	CGPUSemaphoreId render_finished_semaphore;
	uint32_t current_frame_index;
	FrameInfo info;
	CGPURootSignatureId root_sig;
	CGPURenderPipelineId pipeline;
} oval_cgpu_device_t;

void oval_log(void* user_data, ECGPULogSeverity severity, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

size_t malloced = 0;
void* oval_malloc(void* user_data, size_t size, const void* pool)
{
	malloced += size;
	return malloc(size);
}

void* oval_realloc(void* user_data, void* ptr, size_t size, const void* pool)
{
	malloced -= ptr ? _msize(ptr) : 0;
	malloced += size;
	return realloc(ptr, size);
}

void* oval_calloc(void* user_data, size_t count, size_t size, const void* pool)
{
	malloced += count * size;
	return calloc(count, size);
}

void oval_free(void* user_data, void* ptr, const void* pool)
{
	malloced -= ptr ? _msize(ptr) : 0;
	free(ptr);
}

size_t aligned_malloced = 0;
void* oval_malloc_aligned(void* user_data, size_t size, size_t alignment, const void* pool)
{
	aligned_malloced += size;
	return _aligned_malloc(size, alignment);
}

void* oval_realloc_aligned(void* user_data, void* ptr, size_t size, size_t alignment, const void* pool)
{
	aligned_malloced -= ptr ? _aligned_msize(ptr, alignment, 0) : 0;
	aligned_malloced += size;
	return _aligned_realloc(ptr, size, alignment);
}

void* oval_calloc_aligned(void* user_data, size_t count, size_t size, size_t alignment, const void* pool)
{
	aligned_malloced += count * size;
	void* memory = _aligned_malloc(count * size, alignment);
	if (memory != NULL) memset(memory, 0, count * size);
	return memory;
}

void oval_free_aligned(void* user_data, void* ptr, size_t alignment, const void* pool)
{
	aligned_malloced -= ptr ? _aligned_msize(ptr, alignment, 0) : 0;
	_aligned_free(ptr);
}

std::vector<char> readFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}

std::tuple<CGPURootSignatureId, CGPURenderPipelineId> oval_create_render_pipeline(CGPUDeviceId device, ECGPUFormat format, const std::string& vertPath, const std::string& fragPath, CGPURenderPassId render_pass, uint32_t subpass)
{
	CGPUVertexLayout vertex_layout = { 
		.attribute_count = 1,
		.attributes = {
			{ u8"POSITION", 1, CGPU_FORMAT_R32G32_SFLOAT, 0, 0, sizeof(oval_point_t), CGPU_INPUT_RATE_VERTEX },
		},
	};
	CGPUBlendStateDescriptor blend_state = {
		.src_factors = { CGPU_BLEND_CONST_ONE },
		.dst_factors = { CGPU_BLEND_CONST_ZERO },
		.src_alpha_factors = { CGPU_BLEND_CONST_ONE },
		.dst_alpha_factors = { CGPU_BLEND_CONST_ZERO },
		.blend_modes = { CGPU_BLEND_MODE_ADD },
		.blend_alpha_modes = { CGPU_BLEND_MODE_ADD },
		.masks = { CGPU_COLOR_MASK_ALL },
		.alpha_to_coverage = false,
		.independent_blend = false,
	};
	CGPUDepthStateDesc depth_state = {
		.depth_test = false,
		.depth_write = false,
		.stencil_test = false,
	};
	CGPURasterizerStateDescriptor rasterizer_state = {
	.cull_mode = CGPU_CULL_MODE_NONE,
	};

	auto vertShaderCode = readFile(vertPath);
	auto fragShaderCode = readFile(fragPath);
	CGPUShaderLibraryDescriptor vs_desc = {
		.name = u8"VertexShaderLibrary",
		.code = reinterpret_cast<const uint32_t*>(vertShaderCode.data()),
		.code_size = (uint32_t)vertShaderCode.size(),
		.stage = CGPU_SHADER_STAGE_VERT,
	};
	CGPUShaderLibraryDescriptor ps_desc = {
		.name = u8"FragmentShaderLibrary",
		.code = reinterpret_cast<const uint32_t*>(fragShaderCode.data()),
		.code_size = (uint32_t)fragShaderCode.size(),
		.stage = CGPU_SHADER_STAGE_FRAG,
	};
	CGPUShaderLibraryId vertex_shader = cgpu_create_shader_library(device, &vs_desc);
	CGPUShaderLibraryId fragment_shader = cgpu_create_shader_library(device, &ps_desc);
	CGPUShaderEntryDescriptor ppl_shaders[2];
	ppl_shaders[0].stage = CGPU_SHADER_STAGE_VERT;
	ppl_shaders[0].entry = u8"main";
	ppl_shaders[0].library = vertex_shader;
	ppl_shaders[1].stage = CGPU_SHADER_STAGE_FRAG;
	ppl_shaders[1].entry = u8"main";
	ppl_shaders[1].library = fragment_shader;
	CGPURootSignatureDescriptor rs_desc = {
		.shaders = ppl_shaders,
		.shader_count = 2
	};
	auto root_sig = cgpu_create_root_signature(device, &rs_desc);
	ECGPUFormat formats[1] = { format };
	CGPURenderPipelineDescriptor rp_desc = {
		.root_signature = root_sig,
		.vertex_shader = &ppl_shaders[0],
		.fragment_shader = &ppl_shaders[1],
		.vertex_layout = &vertex_layout,
		.blend_state = &blend_state,
		.depth_state = &depth_state,
		.rasterizer_state = &rasterizer_state,
		.render_pass = render_pass,
		.subpass = subpass,
		.render_target_count = 1,
		.prim_topology = CGPU_PRIM_TOPO_TRI_LIST,
	};
	auto pipeline = cgpu_create_render_pipeline(device, &rp_desc);
	cgpu_free_shader_library(vertex_shader);
	cgpu_free_shader_library(fragment_shader);
	return { root_sig, pipeline };
}

oval_device_t* oval_create_device(uint16_t width, uint16_t height, oval_on_draw on_draw)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return nullptr;

	SDL_Window* window = SDL_CreateWindow("oval", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
	if (window == nullptr)
	{
		SDL_Quit();
		return nullptr;
	}

	auto device_cgpu = new oval_cgpu_device_t();
	device_cgpu->super.on_draw = on_draw;
	device_cgpu->super.width = width;
	device_cgpu->super.height = height;
	device_cgpu->window = window;

	CGPUInstanceDescriptor instance_desc = {
		.backend = CGPU_BACKEND_VULKAN,
		.enable_debug_layer = true,
		.enable_gpu_based_validation = true,
		.enable_set_name = true,
		.logger = {
			.log_callback = oval_log
		},
		.allocator = {
			.malloc_fn = oval_malloc,
			.realloc_fn = oval_realloc,
			.calloc_fn = oval_calloc,
			.free_fn = oval_free,
			.malloc_aligned_fn = oval_malloc_aligned,
			.realloc_aligned_fn = oval_realloc_aligned,
			.calloc_aligned_fn = oval_calloc_aligned,
			.free_aligned_fn = oval_free_aligned,
		},
	};
	device_cgpu->instance = cgpu_create_instance(&instance_desc);

	uint32_t adapters_count = 0;
	cgpu_enum_adapters(device_cgpu->instance, CGPU_NULLPTR, &adapters_count);
	CGPUAdapterId* adapters = (CGPUAdapterId*)_alloca(sizeof(CGPUAdapterId) * (adapters_count));
	cgpu_enum_adapters(device_cgpu->instance, adapters, &adapters_count);
	auto adapter = adapters[0];

	// Create device
	CGPUQueueGroupDescriptor G = {
		.queue_type = CGPU_QUEUE_TYPE_GRAPHICS,
		.queue_count = 1
	};
	CGPUDeviceDescriptor device_desc = {
		.queue_groups = &G,
		.queue_group_count = 1
	};
	device_cgpu->device = cgpu_create_device(adapter, &device_desc);
	device_cgpu->gfx_queue = cgpu_get_queue(device_cgpu->device, CGPU_QUEUE_TYPE_GRAPHICS, 0);
	device_cgpu->present_queue = device_cgpu->gfx_queue;

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	device_cgpu->surface = cgpu_surface_from_hwnd(device_cgpu->device, wmInfo.info.win.window);

	ECGPUFormat swapchainFormat = CGPU_FORMAT_R8G8B8A8_UNORM;
	CGPUSwapChainDescriptor descriptor = {
		.present_queues = &device_cgpu->present_queue,
		.present_queues_count = 1,
		.surface = device_cgpu->surface,
		.image_count = 3,
		.width = width,
		.height = height,
		.enable_vsync = true,
		.format = swapchainFormat,
	};
	device_cgpu->swapchain = cgpu_create_swapchain(device_cgpu->device, &descriptor);

	CGPUColorAttachment color_attachments = {
		.format = CGPU_FORMAT_R8G8B8A8_UNORM,
		.load_action = CGPU_LOAD_ACTION_CLEAR,
		.store_action = CGPU_STORE_ACTION_STORE,
	};

	CGPURenderPassDescriptor render_pass_descriptor = {
		.name = u8"Oval_Render_Pass",
		.sample_count = CGPU_SAMPLE_COUNT_1,
		.color_attachments = &color_attachments,
		.depth_stencil = nullptr,
		.render_target_count = 1,
	};
	device_cgpu->render_pass = cgpu_create_render_pass(device_cgpu->device, &render_pass_descriptor);

	for (uint32_t i = 0; i < device_cgpu->swapchain->buffer_count; i++)
	{
		CGPUTextureViewDescriptor view_desc = {
			.texture = device_cgpu->swapchain->back_buffers[i],
			.format = device_cgpu->swapchain->back_buffers[i]->info->format,
			.usages = CGPU_TVU_RTV_DSV,
			.aspects = CGPU_TVA_COLOR,
			.dims = CGPU_TEX_DIMENSION_2D,
			.array_layer_count = 1,
		};
		device_cgpu->swapchain_views[i] = cgpu_create_texture_view(device_cgpu->device, &view_desc);

		CGPUFramebufferDescriptor framebuffer_desc = {
			.renderpass = device_cgpu->render_pass,
			.attachment_count = 1,
			.attachments = &device_cgpu->swapchain_views[i],
			.width = width,
			.height = height,
			.layers = 1,
		};
		device_cgpu->swapchain_framebuffer[i] = cgpu_create_framebuffer(device_cgpu->device, &framebuffer_desc);

		device_cgpu->swapchain_prepared_semaphores[i] = cgpu_create_semaphore(device_cgpu->device);
	}

	for (int i = 0; i < 3; ++i)
	{
		device_cgpu->frameDatas[i].inflightFence = cgpu_create_fence(device_cgpu->device);
		device_cgpu->frameDatas[i].pool = cgpu_create_command_pool(device_cgpu->gfx_queue, CGPU_NULLPTR);
	}

	device_cgpu->render_finished_semaphore = cgpu_create_semaphore(device_cgpu->device);

	auto [root_sig, pipeline] = oval_create_render_pipeline(device_cgpu->device, swapchainFormat, "shaders/oval.vert.spv", "shaders/oval.frag.spv", device_cgpu->render_pass, 0);
	device_cgpu->root_sig = root_sig;
	device_cgpu->pipeline = pipeline;

	return (oval_device_t*)device_cgpu;
}

void oval_runloop(oval_device_t* device)
{
	auto D = (oval_cgpu_device_t*)device;

	// 窗口循环
	SDL_Event e;
	bool quit = false;

	D->current_frame_index = 0;

	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;

			auto& cur_frame_data = D->frameDatas[D->current_frame_index];
			cgpu_wait_fences(&cur_frame_data.inflightFence, 1);
			cur_frame_data.newFrame();
			D->info.reset();

			CGPUAcquireNextDescriptor acquire_desc = {
				.signal_semaphore = D->swapchain_prepared_semaphores[D->current_frame_index],
			};

			D->info.current_swapchain_index = cgpu_acquire_next_image(D->swapchain, &acquire_desc);

			auto back_buffer = D->swapchain->back_buffers[D->info.current_swapchain_index];
			auto back_buffer_view = D->swapchain_views[D->info.current_swapchain_index];
			auto prepared_semaphore = D->swapchain_prepared_semaphores[D->current_frame_index];

			auto cmd = cur_frame_data.request();
			cgpu_cmd_begin(cmd);

			CGPUTextureBarrier draw_barrier = {
				.texture = back_buffer,
				.src_state = CGPU_RESOURCE_STATE_UNDEFINED,
				.dst_state = CGPU_RESOURCE_STATE_RENDER_TARGET
			};
			CGPUResourceBarrierDescriptor barrier_desc0 = { .texture_barriers = &draw_barrier, .texture_barriers_count = 1 };
			cgpu_cmd_resource_barrier(cmd, &barrier_desc0);

			D->info.cmd = cmd;

			D->super.on_draw(device);

			if (D->info.prepared)
			{
				cgpu_cmd_end_render_pass(cmd, D->info.rp_encoder);
			}

			CGPUTextureBarrier present_barrier = {
				.texture = back_buffer,
				.src_state = CGPU_RESOURCE_STATE_RENDER_TARGET,
				.dst_state = CGPU_RESOURCE_STATE_PRESENT
			};
			CGPUResourceBarrierDescriptor barrier_desc1 = { .texture_barriers = &present_barrier, .texture_barriers_count = 1 };
			cgpu_cmd_resource_barrier(cmd, &barrier_desc1);

			cgpu_cmd_end(cmd);

			CGPUQueueSubmitDescriptor submit_desc = {
				.cmds = cur_frame_data.allocated_cmds.data(),
				.signal_fence = cur_frame_data.inflightFence,
				.wait_semaphores = &prepared_semaphore,
				.signal_semaphores = &D->render_finished_semaphore,
				.cmds_count = (uint32_t)cur_frame_data.allocated_cmds.size(),
				.wait_semaphore_count = 1,
				.signal_semaphore_count = 1,
			};
			cgpu_submit_queue(D->gfx_queue, &submit_desc);

			CGPUQueuePresentDescriptor present_desc = {
				.swapchain = D->swapchain,
				.wait_semaphores = &D->render_finished_semaphore,
				.wait_semaphore_count = 1,
				.index = (uint8_t)D->info.current_swapchain_index,
			};
			cgpu_queue_present(D->present_queue, &present_desc);

			D->current_frame_index = (D->current_frame_index + 1) % D->swapchain->buffer_count;
		}
	}
}

void oval_free_device(oval_device_t* device)
{
	auto D = (oval_cgpu_device_t*)device;

	cgpu_wait_queue_idle(D->gfx_queue);

	cgpu_free_root_signature(D->root_sig);
	cgpu_free_render_pipeline(D->pipeline);

	for (uint32_t i = 0; i < D->swapchain->buffer_count; i++)
	{
		cgpu_free_texture_view(D->swapchain_views[i]);
		D->swapchain_views[i] = CGPU_NULLPTR;
		cgpu_free_framebuffer(D->swapchain_framebuffer[i]);
		D->swapchain_framebuffer[i] = CGPU_NULLPTR;
		cgpu_free_semaphore(D->swapchain_prepared_semaphores[i]);
		D->swapchain_prepared_semaphores[i] = CGPU_NULLPTR;
	}

	cgpu_free_swapchain(D->swapchain);
	D->swapchain = CGPU_NULLPTR;
	cgpu_free_surface(D->device, D->surface);
	D->surface = CGPU_NULLPTR;
	
	cgpu_free_semaphore(D->render_finished_semaphore);
	D->render_finished_semaphore = CGPU_NULLPTR;

	for (int i = 0; i < 3; ++i)
	{
		D->frameDatas[i].free();
	}

	cgpu_free_render_pass(D->render_pass);
	D->render_pass = CGPU_NULLPTR;

	cgpu_free_queue(D->gfx_queue);
	D->gfx_queue = CGPU_NULLPTR;
	D->present_queue = CGPU_NULLPTR;
	cgpu_free_device(D->device);
	D->device = CGPU_NULLPTR;
	cgpu_free_instance(D->instance);
	D->instance = CGPU_NULLPTR;

	// 销毁窗口
	SDL_DestroyWindow(D->window);
	// 退出 SDL
	SDL_Quit();

	delete D;
}

void oval_draw_clear(oval_device_t* device, oval_color_t color)
{
	auto D = (oval_cgpu_device_t*)device;
	if (D->info.prepared)
	{
		return;
	}

	const CGPUClearValue clearColor = {
	.color = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1 },
	.is_color = true,
	};

	CGPUBeginRenderPassInfo begin_info = {
		.render_pass = D->render_pass,
		.framebuffer = D->swapchain_framebuffer[D->info.current_swapchain_index],
		.clear_value_count = 1,
		.clear_values = &clearColor,
	};

	D->info.rp_encoder = cgpu_cmd_begin_render_pass(D->info.cmd, &begin_info);

	D->info.prepared = true;

	cgpu_render_encoder_set_viewport(D->info.rp_encoder,
		0.0f, 0.0f,
		(float)device->width, (float)device->height,
		0.f, 1.f);
	cgpu_render_encoder_set_scissor(D->info.rp_encoder, 0, 0, device->width, device->height);
}

void oval_draw_lines(oval_device_t* device, oval_point_t* points, uint32_t count)
{
	auto D = (oval_cgpu_device_t*)device;
	if (!D->info.prepared)
	{
		return;
	}

	uint64_t size = sizeof(oval_point_t) * count;
	CGPUBufferDescriptor buffer_desc = {
		.size = size,
		.name = u8"oval_vertex_buffer",
		.descriptors = CGPU_RESOURCE_TYPE_VERTEX_BUFFER,
		.memory_usage = CGPU_MEM_USAGE_GPU_ONLY,
		.flags = CGPU_BCF_HOST_VISIBLE,
		.start_state = CGPU_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
	};
	auto vertex_buffer = cgpu_create_buffer(D->device, &buffer_desc);
	auto& cur_frame_data = D->frameDatas[D->current_frame_index];
	cur_frame_data.vertex_buffers.push_back(vertex_buffer);

	CGPUBufferRange range = { .offset = 0, .size = size };
	cgpu_map_buffer(vertex_buffer, &range);
	auto vtx_dst = (oval_point_t*)vertex_buffer->info->cpu_mapped_address;
	memcpy(vtx_dst, points, size);
	cgpu_unmap_buffer(vertex_buffer);

	uint32_t vert_strid = sizeof(oval_point_t);
	cgpu_render_encoder_bind_vertex_buffers(D->info.rp_encoder, 1, &vertex_buffer, &vert_strid, 0);
	cgpu_render_encoder_bind_pipeline(D->info.rp_encoder, D->pipeline);
	cgpu_render_encoder_draw(D->info.rp_encoder, count, 0);
}

void oval_draw_commit(oval_device_t* device)
{
	auto D = (oval_cgpu_device_t*)device;
}
