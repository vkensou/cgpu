#include <iostream>
#include <SDL.h>
#include "cgpu/api.h"
#include "SDL_syswm.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv)
{
	// 定义 SDL 窗口
	SDL_Window* window = nullptr;
	// 初始化 SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "[Error]: SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		// 创建窗口
		SDL_Window* window = SDL_CreateWindow("HelloSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
		if (window == nullptr)
		{
			std::cout << "[Error]: Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
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
			auto present_fence = cgpu_create_fence(device);

			SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);
			SDL_GetWindowWMInfo(window, &wmInfo);
			auto surface = cgpu_surface_from_hwnd(device, wmInfo.info.win.window);

			CGPUSwapChainDescriptor descriptor = {
				.present_queues = &gfx_queue,
				.present_queues_count = 1,
				.surface = surface,
				.image_count = 3,
				.width = SCREEN_WIDTH,
				.height = SCREEN_HEIGHT,
				.enable_vsync = true,
				.format = CGPU_FORMAT_R8G8B8A8_UNORM,
			};
			auto swapchain = cgpu_create_swapchain(device, &descriptor);
			CGPUTextureViewId views[3];

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
				views[i] = cgpu_create_texture_view(device, &view_desc);
			}

			auto pool = cgpu_create_command_pool(gfx_queue, CGPU_NULLPTR);
			CGPUCommandBufferDescriptor cmd_desc = { .is_secondary = false };
			auto cmd = cgpu_create_command_buffer(pool, &cmd_desc);

			// 窗口循环
			SDL_Event e;
			bool quit = false;
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
						quit = true;
				}

				cgpu_wait_fences(&present_fence, 1);
				CGPUAcquireNextDescriptor acquire_desc = {
					.fence = present_fence
				};

				auto backbuffer_index = cgpu_acquire_next_image(swapchain, &acquire_desc);
				if (backbuffer_index >= swapchain->buffer_count)
					continue;
				const CGPUTextureId back_buffer = swapchain->back_buffers[backbuffer_index];
				const CGPUTextureViewId back_buffer_view = views[backbuffer_index];

				cgpu_reset_command_pool(pool);
				cgpu_cmd_begin(cmd);

				cgpu_cmd_end(cmd);
				// submit
				CGPUQueueSubmitDescriptor submit_desc = {
					.cmds = &cmd,
					.cmds_count = 1,
				};
				cgpu_submit_queue(gfx_queue, &submit_desc);

				cgpu_wait_queue_idle(gfx_queue);
				CGPUQueuePresentDescriptor present_desc = {
					.swapchain = swapchain,
					.wait_semaphores = CGPU_NULLPTR,
					.wait_semaphore_count = 0,
					.index = (uint8_t)backbuffer_index,
				};
				cgpu_queue_present(gfx_queue, &present_desc);
			}

			cgpu_wait_queue_idle(gfx_queue);
			cgpu_wait_fences(&present_fence, 1);

			for (uint32_t i = 0; i < swapchain->buffer_count; i++)
			{
				cgpu_free_texture_view(views[i]);
			}
			cgpu_free_swapchain(swapchain);
			cgpu_free_surface(device, surface);

			cgpu_free_fence(present_fence);
			cgpu_free_queue(gfx_queue);
			cgpu_free_device(device);
			cgpu_free_instance(instance);
		}
	}
	// 销毁窗口
	SDL_DestroyWindow(window);
	// 退出 SDL
	SDL_Quit();
	return 0;
}
