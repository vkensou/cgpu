#include <iostream>
#include <SDL.h>
#include "cgpu/api.h"

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

			// 获取窗口所包含的表面
			SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

			// 将表面填充为蓝色
			SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 51, 76, 204));

			// 更新表面
			SDL_UpdateWindowSurface(window);

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
			}

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
