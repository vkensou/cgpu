#include <iostream>
#include <SDL.h>
#include "cgpu/api.h"
#include "SDL_syswm.h"
#include <fstream>
#include <vector>
#include <tuple>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_cgpu.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct RenderWindow
{
	SDL_Window* window = nullptr;
	SDL_SysWMinfo wmInfo;
	CGPUSurfaceId surface = CGPU_NULLPTR;
	CGPUSwapChainId swapchain = CGPU_NULLPTR;
	CGPUTextureViewId swapchain_views[3] = { CGPU_NULLPTR };
	CGPUSemaphoreId swapchain_prepared_semaphores[3] = { CGPU_NULLPTR };
	CGPUDeviceId device = CGPU_NULLPTR;
	CGPUQueueId present_queue = CGPU_NULLPTR;
	uint32_t current_swapchain_index = 0;
	uint32_t current_frame_index = 0;

	RenderWindow(CGPUDeviceId device, CGPUQueueId present_queue, int width, int height, Uint32 flags)
	{
		this->device = device;
		this->present_queue = present_queue;

		window = SDL_CreateWindow("HelloSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(window, &wmInfo);

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
		for (uint32_t i = 0; i < swapchain->buffer_count; i++)
		{
			cgpu_free_texture_view(swapchain_views[i]);
		}
		cgpu_free_swapchain(swapchain);
		cgpu_free_surface(device, surface);
	}

	void FreeSyncObjects()
	{
		for (uint32_t i = 0; i < swapchain->buffer_count; i++)
		{
			cgpu_free_semaphore(swapchain_prepared_semaphores[i]);
		}
	}

	void CreateGPUResources()
	{
		surface = cgpu_surface_from_hwnd(device, wmInfo.info.win.window);

		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		CGPUSwapChainDescriptor descriptor = {
			.present_queues = &present_queue,
			.present_queues_count = 1,
			.surface = surface,
			.image_count = 3,
			.width = (uint32_t)w,
			.height = (uint32_t)h,
			.enable_vsync = true,
			.format = CGPU_FORMAT_R8G8B8A8_UNORM,
		};
		swapchain = cgpu_create_swapchain(device, &descriptor);

		for (uint32_t i = 0; i < swapchain->buffer_count; i++)
		{
			CGPUTextureViewDescriptor view_desc = {
				.texture = swapchain->back_buffers[i],
				.format = swapchain->back_buffers[i]->info->format,
				.usages = CGPU_TVU_RTV_DSV,
				.aspects = CGPU_TVA_COLOR,
				.dims = CGPU_TEX_DIMENSION_2D,
				.array_layer_count = 1,
			};
			swapchain_views[i] = cgpu_create_texture_view(device, &view_desc);
		}
	}

	void CreateSyncObjects()
	{
		for (uint32_t i = 0; i < 3; ++i)
		{
			swapchain_prepared_semaphores[i] = cgpu_create_semaphore(device);
		}
	}

	void OnResize()
	{
		FreeGPUResources();
		CreateGPUResources();
	}

	std::tuple<bool, CGPUTextureId, CGPUTextureViewId, CGPUSemaphoreId> AcquireNextImage()
	{
		CGPUAcquireNextDescriptor acquire_desc = {
			.signal_semaphore = swapchain_prepared_semaphores[current_frame_index],
		};

		current_swapchain_index = cgpu_acquire_next_image(swapchain, &acquire_desc);
		if (current_swapchain_index < swapchain->buffer_count)
			return { true, swapchain->back_buffers[current_swapchain_index], swapchain_views[current_swapchain_index], swapchain_prepared_semaphores[current_frame_index] };
		else
			return { false, CGPU_NULLPTR, CGPU_NULLPTR, CGPU_NULLPTR };
	}

	void Present(CGPUSemaphoreId present_signal)
	{
		CGPUQueuePresentDescriptor present_desc = {
			.swapchain = swapchain,
			.wait_semaphores = &present_signal,
			.wait_semaphore_count = 1,
			.index = (uint8_t)current_swapchain_index,
		};
		cgpu_queue_present(present_queue, &present_desc);

		current_frame_index = (current_frame_index + 1) % 3;
	}
};

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

std::tuple<CGPURootSignatureId, CGPURenderPipelineId> create_render_pipeline(CGPUDeviceId device, ECGPUFormat format, const std::string& vertPath, const std::string& fragPath, const CGPUVertexLayout* vertex_layout, CGPUBlendStateDescriptor* blend_state, CGPUDepthStateDesc* depth_state, CGPURasterizerStateDescriptor* rasterizer_state)
{
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
		.vertex_layout = vertex_layout,
		.blend_state = blend_state,
		.depth_state = depth_state,
		.rasterizer_state = rasterizer_state,
		.color_formats = formats,
		.render_target_count = 1,
		.prim_topology = CGPU_PRIM_TOPO_TRI_LIST,
	};
	auto pipeline = cgpu_create_render_pipeline(device, &rp_desc);
	cgpu_free_shader_library(vertex_shader);
	cgpu_free_shader_library(fragment_shader);
	return { root_sig, pipeline };
}

int main(int argc, char** argv)
{
	CGPUInstanceDescriptor instance_desc = {
		.backend = CGPU_BACKEND_VULKAN,
		.enable_debug_layer = true,
		.enable_gpu_based_validation = true,
		.enable_set_name = true
	};
	auto instance = cgpu_create_instance(&instance_desc);

	uint32_t adapters_count = 0;
	cgpu_enum_adapters(instance, CGPU_NULLPTR, &adapters_count);
	CGPUAdapterId* adapters = (CGPUAdapterId*)_alloca(sizeof(CGPUAdapterId) * (adapters_count));
	cgpu_enum_adapters(instance, adapters, &adapters_count);
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
	auto device = cgpu_create_device(adapter, &device_desc);
	auto gfx_queue = cgpu_get_queue(device, CGPU_QUEUE_TYPE_GRAPHICS, 0);
	CGPUFenceId inflightFence[3];
	for (int i = 0; i < 3; ++i)
		inflightFence[i] = cgpu_create_fence(device);
	auto render_finished_semaphore = cgpu_create_semaphore(device);
	int current_frame_index = 0;

	// 初始化 SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "[Error]: SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		RenderWindow main_window(device, gfx_queue, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

		if (main_window.window == nullptr)
		{
			std::cout << "[Error]: Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			//ImGui::StyleColorsLight();

			ImGui_ImplSDL2_InitForOther(main_window.window);
			ImGui_ImplCGPU_InitInfo init_info = {};
			init_info.Instance = instance;
			init_info.Device = device;
			init_info.GfxQueue = gfx_queue;
			init_info.PresentQueue = gfx_queue;
			init_info.ImageCount = 3;
			ImGui_ImplCGPU_Init(&init_info);

			CGPUVertexLayout imgui_vertex_layout = { 
				.attribute_count = 3, 
				.attributes = {
					{ u8"POSITION", 1, CGPU_FORMAT_R32G32_SFLOAT, 0, 0, sizeof(float) * 2, CGPU_INPUT_RATE_VERTEX },
					{ u8"TEXCOORD", 1, CGPU_FORMAT_R32G32_SFLOAT, 0, sizeof(float) * 2, sizeof(float) * 2, CGPU_INPUT_RATE_VERTEX },
					{ u8"COLOR", 1, CGPU_FORMAT_R8G8B8A8_UNORM, 0, sizeof(float) * 4, sizeof(uint32_t), CGPU_INPUT_RATE_VERTEX },
				}
			};
			CGPUBlendStateDescriptor imgui_blend_desc = {
				.src_factors = { CGPU_BLEND_CONST_SRC_ALPHA },
				.dst_factors = { CGPU_BLEND_CONST_ONE_MINUS_SRC_ALPHA },
				.src_alpha_factors = { CGPU_BLEND_CONST_SRC_ALPHA },
				.dst_alpha_factors = { CGPU_BLEND_CONST_ONE_MINUS_SRC_ALPHA },
				.blend_modes = { CGPU_BLEND_MODE_ADD },
				.blend_alpha_modes = { CGPU_BLEND_MODE_ADD },
				.masks = { CGPU_COLOR_MASK_ALL },
				.alpha_to_coverage = false,
				.independent_blend = false,
			};
			CGPUDepthStateDesc imgui_depth_desc = {
				.depth_test = false,
				.depth_write = false,
				.stencil_test = false,
			};
			CGPURasterizerStateDescriptor rasterizer_state = {
				.cull_mode = CGPU_CULL_MODE_NONE,
			};
			auto [imgui_root_sig, imgui_pipeline] = create_render_pipeline(device, main_window.swapchain_views[0]->info.format, "imgui.vert.spv", "imgui.frag.spv", &imgui_vertex_layout, &imgui_blend_desc, &imgui_depth_desc, &rasterizer_state);
			ImGui_ImplCGPU_CreateFontsTexture(gfx_queue, imgui_root_sig);
			ImGui_ImplCGPU_PostInit(imgui_root_sig, imgui_pipeline);

			CGPUVertexLayout vertex_layout = { .attribute_count = 0 };
			CGPUBlendStateDescriptor blend_desc = {
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
			CGPUDepthStateDesc depth_desc = {
				.depth_test = false,
				.depth_write = false,
				.stencil_test = false,
			};
			auto [root_sig, pipeline] = create_render_pipeline(device, main_window.swapchain_views[0]->info.format, "hello.vert.spv", "hello.frag.spv", &vertex_layout, &blend_desc, &depth_desc, nullptr);

			CGPUCommandPoolId pools[3];
			for (int i = 0; i < 3; ++i)
				pools[i] = cgpu_create_command_pool(gfx_queue, CGPU_NULLPTR);

			CGPUCommandBufferId cmds[3];
			CGPUCommandBufferDescriptor cmd_desc = { .is_secondary = false };
			for (int i = 0; i < 3; ++i)
				cmds[i] = cgpu_create_command_buffer(pools[i], &cmd_desc);

			// 窗口循环
			SDL_Event e;
			bool quit = false;
			bool show_demo_window = true;
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
				{
					ImGui_ImplSDL2_ProcessEvent(&e);
					if (e.type == SDL_QUIT)
						quit = true;
					else if (e.type == SDL_WINDOWEVENT)
					{
						if (e.window.windowID == SDL_GetWindowID(main_window.window))
						{
							if (e.window.event == SDL_WINDOWEVENT_CLOSE)
								quit = true;
							else if (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
							{
								cgpu_wait_queue_idle(gfx_queue);

								main_window.OnResize();
							}
						}
					}
				}

				ImGui_ImplCGPU_NewFrame();
				ImGui_ImplSDL2_NewFrame();
				ImGui::NewFrame();

				if (show_demo_window)
					ImGui::ShowDemoWindow(&show_demo_window);

				ImGui::Render();

				current_frame_index = (current_frame_index + 1) % 3;
				cgpu_wait_fences(&inflightFence[current_frame_index], 1);

				auto [acquired, back_buffer, back_buffer_view, prepared_semaphore] = main_window.AcquireNextImage();
				if (!acquired)
					continue;

				cgpu_reset_command_pool(pools[current_frame_index]);
				cgpu_cmd_begin(cmds[current_frame_index]);

				CGPUTextureBarrier draw_barrier = {
					.texture = back_buffer,
					.src_state = CGPU_RESOURCE_STATE_UNDEFINED,
					.dst_state = CGPU_RESOURCE_STATE_RENDER_TARGET
				};
				CGPUResourceBarrierDescriptor barrier_desc0 = { .texture_barriers = &draw_barrier, .texture_barriers_count = 1 };
				cgpu_cmd_resource_barrier(cmds[current_frame_index], &barrier_desc0);

				const CGPUClearValue clearColor = {
					{ 0.f, 0.f, 0.f, 1.f }
				};

				CGPUColorAttachment screen_attachment = {
					.view = back_buffer_view,
					.load_action = CGPU_LOAD_ACTION_CLEAR,
					.store_action = CGPU_STORE_ACTION_STORE,
					.clear_color = clearColor,
				};
				CGPURenderPassDescriptor rp_desc = {
					.sample_count = CGPU_SAMPLE_COUNT_1,
					.color_attachments = &screen_attachment,
					.depth_stencil = CGPU_NULLPTR,
					.render_target_count = 1,
				};
				CGPURenderPassEncoderId rp_encoder = cgpu_cmd_begin_render_pass(cmds[current_frame_index], &rp_desc);

				cgpu_render_encoder_set_viewport(rp_encoder,
					0.0f, 0.0f,
					(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT,
					0.f, 1.f);
				cgpu_render_encoder_set_scissor(rp_encoder, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
				cgpu_render_encoder_bind_pipeline(rp_encoder, pipeline);
				cgpu_render_encoder_draw(rp_encoder, 3, 0);

				ImDrawData* draw_data = ImGui::GetDrawData();
				ImGui_ImplCGPU_RenderDrawData(draw_data, rp_encoder, imgui_root_sig, imgui_pipeline);

				cgpu_cmd_end_render_pass(cmds[current_frame_index], rp_encoder);
				CGPUTextureBarrier present_barrier = {
					.texture = back_buffer,
					.src_state = CGPU_RESOURCE_STATE_RENDER_TARGET,
					.dst_state = CGPU_RESOURCE_STATE_PRESENT
				};
				CGPUResourceBarrierDescriptor barrier_desc1 = { .texture_barriers = &present_barrier, .texture_barriers_count = 1 };
				cgpu_cmd_resource_barrier(cmds[current_frame_index], &barrier_desc1);

				cgpu_cmd_end(cmds[current_frame_index]);
				// submit
				CGPUQueueSubmitDescriptor submit_desc = {
					.cmds = &cmds[current_frame_index],
					.signal_fence = inflightFence[current_frame_index],
					.wait_semaphores = &prepared_semaphore,
					.signal_semaphores = &render_finished_semaphore,
					.cmds_count = 1,
					.wait_semaphore_count = 1,
					.signal_semaphore_count = 1,
				};
				cgpu_submit_queue(gfx_queue, &submit_desc);

				main_window.Present(render_finished_semaphore);

				// Update and Render additional Platform Windows
				if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				{
					ImGui::UpdatePlatformWindows();
					ImGui::RenderPlatformWindowsDefault();
				}
			}

			cgpu_wait_queue_idle(gfx_queue);

			for (int i = 0; i < 3; ++i)
				cgpu_free_command_buffer(cmds[i]);
			for (int i = 0; i < 3; ++i)
				cgpu_free_command_pool(pools[i]);

			ImGui_ImplCGPU_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();

			cgpu_free_render_pipeline(imgui_pipeline);
			cgpu_free_root_signature(imgui_root_sig);

			cgpu_free_render_pipeline(pipeline);
			cgpu_free_root_signature(root_sig);
		}
	}

	// 退出 SDL
	SDL_Quit();

	cgpu_free_semaphore(render_finished_semaphore);
	for (int i = 0; i < 3; ++i)
		cgpu_free_fence(inflightFence[i]);
	cgpu_free_queue(gfx_queue);
	cgpu_free_device(device);
	cgpu_free_instance(instance);

	return 0;
}
