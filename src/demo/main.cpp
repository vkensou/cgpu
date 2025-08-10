#include <iostream>
#include <SDL3/SDL.h>
#include "cgpu/api.h"
#include <fstream>
#include <vector>
#include <tuple>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_cgpu.h"
#include <stdarg.h>
#include "renderdoc_helper.h"
#include "GpuTimeStamps.h"
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

CGPUInstanceId instance;
CGPUDeviceId device;
CGPUQueueId gfx_queue;
CGPURenderPassId render_pass;
GpuTimeStamps* gpu_timer;
std::vector<TimeStamp> stamps;

struct RenderWindow;
std::vector<RenderWindow*> windows;

CGPURootSignatureId imgui_root_sig;
CGPURenderPipelineId imgui_pipeline;
CGPURootSignatureId root_sig;
CGPURenderPipelineId pipeline;

struct FrameData
{
	CGPUFenceId inflightFence;
	CGPUCommandPoolId pool;
	std::vector<CGPUCommandBufferId> cmds;
	std::vector<CGPUCommandBufferId> allocated_cmds;

	void newFrame()
	{
		cgpu_command_pool_reset(pool);

		for (auto cmd : allocated_cmds)
			cmds.push_back(cmd);
		allocated_cmds.clear();
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
			cmd = cgpu_command_pool_create_command_buffer(pool, &cmd_desc);
		}

		allocated_cmds.push_back(cmd);
		return cmd;
	}

	void free()
	{
		cgpu_device_free_fence(device, inflightFence);
		inflightFence = CGPU_NULLPTR;

		for (auto cmd : cmds)
			cgpu_command_pool_free_command_buffer(pool, cmd);
		cmds.clear();

		for (auto cmd : allocated_cmds)
			cgpu_command_pool_free_command_buffer(pool, cmd);
		allocated_cmds.clear();

		cgpu_queue_free_command_pool(pool->queue, pool);
		pool = CGPU_NULLPTR;
	}
};

struct RenderWindow
{
	SDL_Window* window = nullptr;
	SDL_WindowID windowId = 0;
	ImGuiViewport* imgui_viewport;
	CGPUSurfaceId surface = CGPU_NULLPTR;
	CGPUSwapChainId swapchain = CGPU_NULLPTR;
	CGPUTextureViewId swapchain_views[3] = { CGPU_NULLPTR };
	CGPUSemaphoreId swapchain_prepared_semaphores[3] = { CGPU_NULLPTR };
	CGPUFramebufferId swapchain_framebuffer[3] = { CGPU_NULLPTR };
	CGPUDeviceId device = CGPU_NULLPTR;
	CGPUQueueId present_queue = CGPU_NULLPTR;
	CGPURenderPassId render_pass;
	uint32_t current_swapchain_index = 0;
	uint32_t current_frame_index = 0;
	bool needResize = false;
	bool owned_window;

	CGPURenderPipelineId pipeline = CGPU_NULLPTR;
	CGPURootSignatureId imgui_root_sig;
	CGPURenderPipelineId imgui_pipeline;

	RenderWindow(CGPUDeviceId device, CGPUQueueId present_queue, CGPURenderPassId render_pass, int width, int height)
	{
		this->device = device;
		this->present_queue = present_queue;
		this->render_pass = render_pass;

		SDL_PropertiesID props = SDL_CreateProperties();
		SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Hello CGPU");
		SDL_SetFloatProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
		SDL_SetFloatProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
		SDL_SetFloatProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
		SDL_SetFloatProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
		SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
		SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_EXTERNAL_GRAPHICS_CONTEXT_BOOLEAN, true);

		window = SDL_CreateWindowWithProperties(props);
		windowId = SDL_GetWindowID(window);
		auto window_props = SDL_GetWindowProperties(window);
		SDL_SetPointerProperty(window_props, "sdl.window.userdata", this);
		
		SDL_DestroyProperties(props);
		owned_window = true;

		CreateGPUResources();
		CreateSyncObjects();
	}

	RenderWindow(CGPUDeviceId device, CGPUQueueId present_queue, CGPURenderPassId render_pass, SDL_Window* window)
	{
		this->device = device;
		this->present_queue = present_queue;
		this->render_pass = render_pass;

		this->window = window;
		owned_window = false;

		CreateGPUResources();
		CreateSyncObjects();
	}

	~RenderWindow()
	{
		FreeSyncObjects();
		FreeGPUResources();
	}

	void FreeGPUResources()
	{
		if (!swapchain)
			return;

		for (uint32_t i = 0; i < swapchain->buffer_count; i++)
		{
			cgpu_device_free_texture_view(device, swapchain_views[i]);
			swapchain_views[i] = CGPU_NULLPTR;
			cgpu_device_free_framebuffer(device, swapchain_framebuffer[i]);
			swapchain_framebuffer[i] = CGPU_NULLPTR;
		}
		cgpu_device_free_swap_chain(device, swapchain);
		swapchain = CGPU_NULLPTR;
		cgpu_instance_free_surface(instance, surface);
		surface = CGPU_NULLPTR;
	}

	void FreeSyncObjects()
	{
		for (uint32_t i = 0; i < swapchain->buffer_count; i++)
		{
			cgpu_device_free_semaphore(device, swapchain_prepared_semaphores[i]);
		}
	}

	void CreateGPUResources()
	{
		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
			return;

		auto window_props = SDL_GetWindowProperties(window);
		auto hwnd = SDL_GetPointerProperty(window_props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
		surface = cgpu_instance_create_surface_from_native_view(instance, hwnd);

		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		CGPUSwapChainDescriptor descriptor = {
			.present_queue_count = 1,
			.p_present_queues = &present_queue,
			.surface = surface,
			.image_count = 3,
			.width = (uint32_t)w,
			.height = (uint32_t)h,
			.enable_vsync = true,
			.format = CGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM,
		};
		swapchain = cgpu_device_create_swap_chain(device, &descriptor);

		for (uint32_t i = 0; i < swapchain->buffer_count; i++)
		{
			CGPUTextureViewDescriptor view_desc = {
				.texture = swapchain->back_buffers[i],
				.format = swapchain->back_buffers[i]->info->format,
				.usages = CGPU_TEXTURE_VIEW_USAGE_RTV_DSV,
				.aspects = CGPU_TEXTURE_VIEW_ASPECT_COLOR,
				.dims = CGPU_TEXTURE_DIMENSION_2D,
				.array_layer_count = 1,
			};
			swapchain_views[i] = cgpu_device_create_texture_view(device, &view_desc);

			CGPUFramebufferDescriptor framebuffer_desc = {
				.renderpass = render_pass,
				.attachment_count = 1,
				.p_attachments = {swapchain_views[i], CGPU_NULLPTR, CGPU_NULLPTR, CGPU_NULLPTR, CGPU_NULLPTR, CGPU_NULLPTR, CGPU_NULLPTR, CGPU_NULLPTR, CGPU_NULLPTR },
				.width = (uint32_t)w,
				.height = (uint32_t)h,
				.layers = 1,
			};
			swapchain_framebuffer[i] = cgpu_device_create_framebuffer(device, &framebuffer_desc);
		}

		needResize = false;
	}

	void CreateSyncObjects()
	{
		for (uint32_t i = 0; i < 3; ++i)
		{
			swapchain_prepared_semaphores[i] = cgpu_device_create_semaphore(device);
		}
	}

	void RequestResize()
	{
		needResize = true;
	}

	void OnResize()
	{
		FreeGPUResources();
		CreateGPUResources();
	}

	bool AcquireNextImage()
	{
		current_frame_index = (current_frame_index + 1) % 3;

		if (!swapchain)
			return false;

		CGPUAcquireNextDescriptor acquire_desc = {
			.signal_semaphore = swapchain_prepared_semaphores[current_frame_index],
		};

		current_swapchain_index = cgpu_swap_chain_acquire_next_image(swapchain, &acquire_desc);
		if (current_swapchain_index < swapchain->buffer_count)
			return true;
		else
			return false;
	}

	void Present(CGPUSemaphoreId present_signal)
	{
		CGPUQueuePresentDescriptor present_desc = {
			.swapchain = swapchain,
			.wait_semaphore_count = 1,
			.p_wait_semaphores = &present_signal,
			.index = (uint8_t)current_swapchain_index,
		};
		cgpu_queue_present(present_queue, &present_desc);
	}

	void Render(CGPUCommandBufferId cmd)
	{
		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		auto back_buffer = swapchain->back_buffers[current_swapchain_index];
		auto back_buffer_view = swapchain_views[current_swapchain_index];
		auto prepared_semaphore = swapchain_prepared_semaphores[current_frame_index];

		CGPUTextureBarrier draw_barrier = {
			.texture = back_buffer,
			.src_state = CGPU_RESOURCE_STATE_UNDEFINED,
			.dst_state = CGPU_RESOURCE_STATE_RENDER_TARGET
		};
		CGPUResourceBarrierDescriptor barrier_desc0 = { .texture_barrier_count = 1, .p_texture_barriers = &draw_barrier, };
		cgpu_command_buffer_resource_barrier(cmd, &barrier_desc0);

		const CGPUClearValue clearColor = {
			.color = { 0.f, 0.f, 0.f, 1.f },
			.is_color = true,
		};

		CGPUBeginRenderPassInfo begin_info = {
			.render_pass = this->render_pass,
			.framebuffer = this->swapchain_framebuffer[current_swapchain_index],
			.clear_value_count = 1,
			.p_clear_values = &clearColor,
		};

		CGPURenderPassEncoderId rp_encoder = cgpu_command_buffer_begin_render_pass(cmd, &begin_info);
		cgpu_render_pass_encoder_set_shading_rate(rp_encoder, CGPU_SHADING_RATE_FULL, CGPU_SHADING_RATE_COMBINER_PASS_THROUGH, CGPU_SHADING_RATE_COMBINER_PASS_THROUGH);
		cgpu_render_pass_encoder_set_viewport(rp_encoder,
			0.0f, 0.0f,
			(float)w, (float)h,
			0.f, 1.f);
		cgpu_render_pass_encoder_set_scissor(rp_encoder, 0, 0, w, h);
		if (pipeline)
		{
			cgpu_render_pass_encoder_bind_render_pipeline(rp_encoder, pipeline);
			cgpu_render_pass_encoder_draw(rp_encoder, 3, 0);
		}

		ImDrawData* draw_data = imgui_viewport->DrawData;
		ImGui_ImplCGPU_RenderDrawData(draw_data, rp_encoder, imgui_root_sig, imgui_pipeline);

		cgpu_command_buffer_end_render_pass(cmd, rp_encoder);
		CGPUTextureBarrier present_barrier = {
			.texture = back_buffer,
			.src_state = CGPU_RESOURCE_STATE_RENDER_TARGET,
			.dst_state = CGPU_RESOURCE_STATE_PRESENT
		};
		CGPUResourceBarrierDescriptor barrier_desc1 = { .texture_barrier_count = 1, .p_texture_barriers = &present_barrier, };
		cgpu_command_buffer_resource_barrier(cmd, &barrier_desc1);
	}
};

static void ImGui_ImplArena_InitPlatformInterface();

std::vector<uint8_t> readFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<uint8_t> buffer(fileSize);

	file.seekg(0);
	file.read((char*)buffer.data(), fileSize);

	file.close();
	return buffer;
}

std::tuple<CGPURootSignatureId, CGPURenderPipelineId> create_render_pipeline(CGPUDeviceId device, ECGPUTextureFormat format, const std::string& vertPath, const std::string& fragPath, const CGPUVertexLayout* vertex_layout, CGPUBlendStateDescriptor* blend_state, CGPUDepthStateDescriptor* depth_state, CGPURasterizerStateDescriptor* rasterizer_state, CGPURenderPassId render_pass, uint32_t subpass)
{
	auto vertShaderCode = readFile(vertPath);
	auto fragShaderCode = readFile(fragPath);
	CGPUShaderLibraryDescriptor vs_desc = {
		.name = "VertexShaderLibrary",
		.code_size = vertShaderCode.size(),
		.p_codes = vertShaderCode.data(),
		.stage = CGPU_SHADER_STAGE_VERTEX,
	};
	CGPUShaderLibraryDescriptor ps_desc = {
		.name = "FragmentShaderLibrary",
		.code_size = fragShaderCode.size(),
		.p_codes = fragShaderCode.data(),
		.stage = CGPU_SHADER_STAGE_FRAGMENT,
	};
	CGPUShaderLibraryId vertex_shader = cgpu_device_create_shader_library(device, &vs_desc);
	CGPUShaderLibraryId fragment_shader = cgpu_device_create_shader_library(device, &ps_desc);
	CGPUShaderEntryDescriptor ppl_shaders[2];
	ppl_shaders[0].stage = CGPU_SHADER_STAGE_VERTEX;
	ppl_shaders[0].entry = "main";
	ppl_shaders[0].library = vertex_shader;
	ppl_shaders[1].stage = CGPU_SHADER_STAGE_FRAGMENT;
	ppl_shaders[1].entry = "main";
	ppl_shaders[1].library = fragment_shader;
	CGPURootSignatureDescriptor rs_desc = {
		.shader_count = 2,
		.p_shaders = ppl_shaders,
	};
	auto root_sig = cgpu_device_create_root_signature(device, &rs_desc);
	ECGPUTextureFormat formats[1] = { format };
	CGPURenderPipelineDescriptor rp_desc = {
		.root_signature = root_sig,
		.vertex_shader = &ppl_shaders[0],
		.fragment_shader = &ppl_shaders[1],
		.vertex_layout = vertex_layout,
		.blend_state = blend_state,
		.depth_state = depth_state,
		.rasterizer_state = rasterizer_state,
		.render_pass = render_pass,
		.subpass = subpass,
		.render_target_count = 1,
		.prim_topology = CGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
	};
	auto pipeline = cgpu_device_create_render_pipeline(device, &rp_desc);
	cgpu_device_free_shader_library(device, vertex_shader);
	cgpu_device_free_shader_library(device, fragment_shader);
	return { root_sig, pipeline };
}

void demo_log(void* user_data, ECGPULogSeverity severity, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

size_t malloced = 0;
void* demo_malloc(void* user_data, size_t size, const void* pool)
{
	if (size == 0)
		return nullptr;
	malloced += size;
	return malloc(size);
}

void* demo_realloc(void* user_data, void* ptr, size_t size, const void* pool)
{
	malloced -= ptr ? _msize(ptr) : 0;
	malloced += size;
	return realloc(ptr, size);
}

void* demo_calloc(void* user_data, size_t count, size_t size, const void* pool)
{
	if (count * size == 0)
		return nullptr;
	malloced += count * size;
	return calloc(count, size);
}

void demo_free(void* user_data, void* ptr, const void* pool)
{
	malloced -= ptr ? _msize(ptr) : 0;
	free(ptr);
}

size_t aligned_malloced = 0;
void* demo_malloc_aligned(void* user_data, size_t size, size_t alignment, const void* pool)
{
	aligned_malloced += size;
	return _aligned_malloc(size, alignment);
}

void* demo_realloc_aligned(void* user_data, void* ptr, size_t size, size_t alignment, const void* pool)
{
	aligned_malloced -= ptr ? _aligned_msize(ptr, alignment, 0) : 0;
	aligned_malloced += size;
	return _aligned_realloc(ptr, size, alignment);
}

void* demo_calloc_aligned(void* user_data, size_t count, size_t size, size_t alignment, const void* pool)
{
	aligned_malloced += count * size;
	void* memory = _aligned_malloc(count * size, alignment);
	if (memory != NULL) memset(memory, 0, count * size);
	return memory;
}

void demo_free_aligned(void* user_data, void* ptr, const void* pool)
{
	aligned_malloced -= ptr ? _aligned_msize(ptr, 1, 0) : 0;
	_aligned_free(ptr);
}

RENDERDOC_API_1_0_0* rdc = nullptr;
bool rdc_capture = false;
CGPUAdapterId adapter;
FrameData frameDatas[3];
CGPUSemaphoreId render_finished_semaphore;
int current_frame_index = -1;
double gpuTicksPerSecond;
RenderWindow* main_window;
std::vector<RenderWindow*> need_resize_windows;
std::vector<RenderWindow*> prepared_windows;
std::vector<CGPUSemaphoreId> wait_semaphores;
bool show_demo_window = true;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
	if (false)
	{
		auto renderdoc_path = locate_renderdoc();
		if (load_renderdoc(renderdoc_path))
			rdc = GetRenderDocApi();
	}

	CGPUInstanceDescriptor instance_desc = {
	.backend = CGPU_BACKEND_VULKAN,
		.enable_debug_layer = true,
		.enable_gpu_based_validation = true,
		.enable_set_name = true,
	.logger = {
		.log_callback = demo_log
	},
	.allocator = {
		.malloc_fn = demo_malloc,
		.realloc_fn = demo_realloc,
		.calloc_fn = demo_calloc,
		.free_fn = demo_free,
		.malloc_aligned_fn = demo_malloc_aligned,
		.realloc_aligned_fn = demo_realloc_aligned,
		.calloc_aligned_fn = demo_calloc_aligned,
		.free_aligned_fn = demo_free_aligned,
	},
	};
	instance = cgpu_create_instance(&instance_desc);

	uint32_t adapters_count = 0;
	cgpu_instance_enum_adapters(instance, &adapters_count, CGPU_NULLPTR);
	CGPUAdapterId* adapters = (CGPUAdapterId*)_alloca(sizeof(CGPUAdapterId) * (adapters_count));
	cgpu_instance_enum_adapters(instance, &adapters_count, adapters);
	adapter = adapters[0];

	// Create device
	CGPUQueueGroupDescriptor G = {
		.queue_type = CGPU_QUEUE_TYPE_GRAPHICS,
		.queue_count = 1,
	};
	CGPUDeviceDescriptor device_desc = {
		.queue_group_count = 1,
		.p_queue_groups = &G,
	};
	device = cgpu_adapter_create_device(adapter, &device_desc);
	gfx_queue = cgpu_device_get_queue(device, CGPU_QUEUE_TYPE_GRAPHICS, 0);

	CGPUColorAttachment color_attachments = {
		.format = CGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM,
		.load_action = CGPU_LOAD_ACTION_CLEAR,
		.store_action = CGPU_STORE_ACTION_STORE,
	};
	CGPURenderPassDescriptor render_pass_descriptor = {
		.sample_count = CGPU_SAMPLE_COUNT_1,
		.color_attachments = {color_attachments, {}, {}, {}, {}, {}, {}, {}},
		.depth_stencil = {},
	};
	render_pass = cgpu_device_create_render_pass(device, &render_pass_descriptor);
	for (int i = 0; i < 3; ++i)
	{
		frameDatas[i].inflightFence = cgpu_device_create_fence(device);
		frameDatas[i].pool = cgpu_queue_create_command_pool(gfx_queue, CGPU_NULLPTR);
	}
	render_finished_semaphore = cgpu_device_create_semaphore(device);

	gpu_timer = new GpuTimeStamps(device, 3);

	gpuTicksPerSecond = cgpu_queue_get_timestamp_period_ns(gfx_queue);

	main_window = new RenderWindow(device, gfx_queue, render_pass, SCREEN_WIDTH, SCREEN_HEIGHT);
	windows.push_back(main_window);

	if (main_window->window == nullptr)
	{
		std::cout << "[Error]: Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return SDL_APP_FAILURE;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGui_ImplSDL3_InitForOther(main_window->window);
	ImGui_ImplCGPU_InitInfo init_info = {};
	init_info.Instance = instance;
	init_info.Device = device;
	init_info.GfxQueue = gfx_queue;
	init_info.PresentQueue = gfx_queue;
	init_info.RenderPass = render_pass;
	init_info.ImageCount = 3;
	ImGui_ImplCGPU_Init(&init_info);
	ImGui_ImplArena_InitPlatformInterface();

	CGPUVertexAttribute imgui_vertex_attributes[3] = {
			{ "POSITION", 1, CGPU_VERTEX_FORMAT_FLOAT32X2, 0, 0, sizeof(float) * 2, CGPU_VERTEX_INPUT_RATE_VERTEX },
			{ "TEXCOORD", 1, CGPU_VERTEX_FORMAT_FLOAT32X2, 0, sizeof(float) * 2, sizeof(float) * 2, CGPU_VERTEX_INPUT_RATE_VERTEX },
			{ "COLOR", 1, CGPU_VERTEX_FORMAT_UNORM8X4, 0, sizeof(float) * 4, sizeof(uint32_t), CGPU_VERTEX_INPUT_RATE_VERTEX },
	};
	CGPUVertexLayout imgui_vertex_layout = {
		.attribute_count = 3,
		.p_attributes = imgui_vertex_attributes,
	};
	CGPUBlendAttachmentState imgui_blend_attachments = {
		.enable = true,
		.src_factor = CGPU_BLEND_FACTOR_SRC_ALPHA,
		.dst_factor = CGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		.src_alpha_factor = CGPU_BLEND_FACTOR_SRC_ALPHA,
		.dst_alpha_factor = CGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		.blend_op = CGPU_BLEND_OP_ADD,
		.blend_alpha_op = CGPU_BLEND_OP_ADD,
		.color_mask = CGPU_COLOR_MASK_RGBA,
	};
	CGPUBlendStateDescriptor imgui_blend_desc = {
		.attachment_count = 1,
		.p_attachments = &imgui_blend_attachments,
		.alpha_to_coverage = false,
		.independent_blend = false,
	};
	CGPUDepthStateDescriptor imgui_depth_desc = {
		.depth_test = false,
		.depth_write = false,
		.stencil_test = false,
	};
	CGPURasterizerStateDescriptor rasterizer_state = {
		.cull_mode = CGPU_CULL_MODE_NONE,
	};
	auto [_imgui_root_sig, _imgui_pipeline] = create_render_pipeline(device, main_window->swapchain_views[0]->info.format, "shaders/imgui.vert.spv", "shaders/imgui.frag.spv", &imgui_vertex_layout, &imgui_blend_desc, &imgui_depth_desc, &rasterizer_state, render_pass, 0);
	imgui_root_sig = _imgui_root_sig;
	imgui_pipeline = _imgui_pipeline;

	ImGui_ImplCGPU_CreateFontsTexture(gfx_queue, imgui_root_sig);
	ImGui_ImplCGPU_PostInit(imgui_root_sig, imgui_pipeline);

	main_window->imgui_viewport = ImGui::GetMainViewport();

	CGPUVertexLayout vertex_layout = { .attribute_count = 0 };
	CGPUBlendAttachmentState blend_attachments = {
		.enable = false,
		.src_factor = CGPU_BLEND_FACTOR_ONE,
		.dst_factor = CGPU_BLEND_FACTOR_ZERO,
		.src_alpha_factor = CGPU_BLEND_FACTOR_ONE,
		.dst_alpha_factor = CGPU_BLEND_FACTOR_ZERO,
		.blend_op = CGPU_BLEND_OP_ADD,
		.blend_alpha_op = CGPU_BLEND_OP_ADD,
		.color_mask = CGPU_COLOR_MASK_RGBA,
	};
	CGPUBlendStateDescriptor blend_desc = {
		.attachment_count = 1,
		.p_attachments = &blend_attachments,
		.alpha_to_coverage = false,
		.independent_blend = false,
	};
	CGPUDepthStateDescriptor depth_desc = {
		.depth_test = false,
		.depth_write = false,
		.stencil_test = false,
	};
	auto [_root_sig, _pipeline] = create_render_pipeline(device, main_window->swapchain_views[0]->info.format, "shaders/hello.vert.spv", "shaders/hello.frag.spv", &vertex_layout, &blend_desc, &depth_desc, nullptr, render_pass, 0);
	root_sig = _root_sig;
	pipeline = _pipeline;

	main_window->pipeline = pipeline;
	main_window->imgui_root_sig = imgui_root_sig;
	main_window->imgui_pipeline = imgui_pipeline;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	need_resize_windows.clear();
	for (auto window : windows)
	{
		if (window->needResize)
			need_resize_windows.push_back(window);
	}

	if (!need_resize_windows.empty())
	{
		cgpu_queue_wait_idle(gfx_queue);
		for (auto window : need_resize_windows)
			window->OnResize();
	}

	ImGui_ImplCGPU_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	if (ImGui::Button("Capture"))
		rdc_capture = true;

	if (stamps.size() > 0)
	{
		for (uint32_t i = 0; i < stamps.size(); ++i)
		{
			//float value = m_UIState.bShowMilliseconds ? timeStamps[i].m_microseconds / 1000.0f : timeStamps[i].m_microseconds;
			//const char* pStrUnit = m_UIState.bShowMilliseconds ? "ms" : "us";
			//ImGui::Text("%-18s: %7.2f %s", timeStamps[i].m_label.c_str(), value, pStrUnit);
			float stamp = stamps[i].duration;
			ImGui::Text("%s %7.2f us", stamps[i].label.c_str(), stamp * 1000);
		}
	}

	if (rdc && rdc_capture)
		rdc->StartFrameCapture(nullptr, nullptr);

	current_frame_index = (current_frame_index + 1) % 3;
	auto& cur_frame_data = frameDatas[current_frame_index];
	cgpu_wait_fences(1, &cur_frame_data.inflightFence);

	prepared_windows.clear();
	for (auto window : windows)
	{
		if (window->AcquireNextImage())
			prepared_windows.push_back(window);
		else
			window->RequestResize();
	}

	if (prepared_windows.empty())
	{
		ImGui::EndFrame();
		return SDL_APP_CONTINUE;
	}

	ImGui::Render();

	cur_frame_data.newFrame();

	auto cmd = cur_frame_data.request();
	cgpu_command_buffer_begin(cmd);

	gpu_timer->OnBeginFrame(cmd, gpuTicksPerSecond, stamps);

	gpu_timer->GetTimeStamp(cmd, "Begin Frame");

	for (auto window : prepared_windows)
	{
		window->Render(cmd);
		gpu_timer->GetTimeStamp(cmd, "Render Window");
	}

	gpu_timer->CollectTimings(cmd);

	cgpu_command_buffer_end(cmd);

	gpu_timer->OnEndFrame();

	wait_semaphores.clear();
	for (auto window : prepared_windows)
	{
		wait_semaphores.push_back(window->swapchain_prepared_semaphores[window->current_frame_index]);
	}

	// submit
	CGPUQueueSubmitDescriptor submit_desc = {
		.cmd_count = (uint32_t)cur_frame_data.allocated_cmds.size(),
		.p_cmds = cur_frame_data.allocated_cmds.data(),
		.signal_fence = cur_frame_data.inflightFence,
		.wait_semaphore_count = (uint32_t)wait_semaphores.size(),
		.p_wait_semaphores = wait_semaphores.data(),
		.signal_semaphore_count = 1,
		.p_signal_semaphores = &render_finished_semaphore,
	};
	cgpu_queue_submit(gfx_queue, &submit_desc);

	for (auto window : prepared_windows)
	{
		window->Present(render_finished_semaphore);
	}

	if (rdc && rdc_capture)
	{
		rdc->EndFrameCapture(nullptr, nullptr);

		if (!rdc->IsRemoteAccessConnected())
		{
			rdc->LaunchReplayUI(1, "");
		}
	}

	ImGuiIO& io = ImGui::GetIO();
	// Update and Render additional Platform Windows
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
	}

	rdc_capture = false;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	ImGui_ImplSDL3_ProcessEvent(event);

	if (event->type == SDL_EVENT_QUIT || (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event->window.windowID == SDL_GetWindowID(main_window->window)))
		return SDL_APP_SUCCESS;

	if (event->type == SDL_EVENT_WINDOW_RESIZED || event->type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
	{
		auto props = SDL_GetWindowProperties(SDL_GetWindowFromEvent(event));
		auto window = (RenderWindow*)SDL_GetPointerProperty(props, "sdl.window.userdata", nullptr);
		if (window)
			window->RequestResize();

		printf("resize\n");
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	cgpu_queue_wait_idle(gfx_queue);

	ImGui_ImplCGPU_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	cgpu_device_free_render_pipeline(device, imgui_pipeline);
	cgpu_device_free_root_signature(device, imgui_root_sig);

	cgpu_device_free_render_pipeline(device, pipeline);
	cgpu_device_free_root_signature(device, root_sig);

	for (auto window : windows)
		delete window;
	windows.clear();

	cgpu_device_free_semaphore(device, render_finished_semaphore);
	for (int i = 0; i < 3; ++i)
	{
		frameDatas[i].free();
	}
	delete gpu_timer;
	cgpu_device_free_render_pass(device, render_pass);
	cgpu_device_free_queue(device, gfx_queue);
	cgpu_adapter_free_device(adapter, device);
	cgpu_free_instance(instance);

	printf("%lld\n", malloced);
	printf("%lld\n", aligned_malloced);
}

static void ImGui_ImplArena_CreateWindow(ImGuiViewport* viewport)
{
	RenderWindow* window = new RenderWindow(device, gfx_queue, render_pass, SDL_GetWindowFromID((unsigned int)(uintptr_t)viewport->PlatformHandle));
	windows.push_back(window);
	ImGui_Arena_ViewportData* vd = IM_NEW(ImGui_Arena_ViewportData)();
	vd->window = window;
	viewport->RendererUserData = vd;

	window->imgui_viewport = viewport;
	window->imgui_root_sig = imgui_root_sig;
	window->imgui_pipeline = imgui_pipeline;
}

static void ImGui_ImplArena_DestroyWindow(ImGuiViewport* viewport)
{
	if (ImGui_Arena_ViewportData* vd = (ImGui_Arena_ViewportData*)viewport->RendererUserData)
	{
		auto window = vd->window;
		windows.erase(std::remove(windows.begin(), windows.end(), window), windows.end());
		delete window;

		ImGui_ImplCGPU_WindowRenderBuffers* wrb = &vd->RenderBuffers;
		for (uint32_t n = 0; n < wrb->Count; n++)
		{
			ImGui_ImplCGPU_FrameRenderBuffers* buffers = &wrb->FrameRenderBuffers[n];
			if (buffers->VertexBuffer) { cgpu_device_free_buffer(device, buffers->VertexBuffer); buffers->VertexBuffer = CGPU_NULLPTR; }
			if (buffers->IndexBuffer) { cgpu_device_free_buffer(device, buffers->IndexBuffer); buffers->IndexBuffer = CGPU_NULLPTR; }
			buffers->VertexBufferSize = 0;
			buffers->IndexBufferSize = 0;
		}
		IM_FREE(wrb->FrameRenderBuffers);
		wrb->FrameRenderBuffers = nullptr;
		wrb->Index = 0;
		wrb->Count = 0;

		IM_FREE(vd);
	}

	viewport->RendererUserData = nullptr;
}

static void ImGui_ImplArena_SetWindowSize(ImGuiViewport* viewport, ImVec2 size)
{
	ImGui_Arena_ViewportData* vd = (ImGui_Arena_ViewportData*)viewport->RendererUserData;
	if (!vd)
		return;

	vd->window->RequestResize();
}

static void ImGui_ImplArena_RenderWindow(ImGuiViewport* viewport, void*)
{
}

static void ImGui_ImplArena_SwapBuffers(ImGuiViewport* viewport, void*)
{
}

void ImGui_ImplArena_InitPlatformInterface()
{
	ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		IM_ASSERT(platform_io.Platform_CreateVkSurface != nullptr && "Platform needs to setup the CreateVkSurface handler.");
	platform_io.Renderer_CreateWindow = ImGui_ImplArena_CreateWindow;
	platform_io.Renderer_DestroyWindow = ImGui_ImplArena_DestroyWindow;
	platform_io.Renderer_SetWindowSize = ImGui_ImplArena_SetWindowSize;
	platform_io.Renderer_RenderWindow = ImGui_ImplArena_RenderWindow;
	platform_io.Renderer_SwapBuffers = ImGui_ImplArena_SwapBuffers;
}
