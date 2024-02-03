#include "oval_device.h"

#include <SDL.h>

typedef struct oval_cgpu_device_t {
	oval_device_t device;
	SDL_Window* window;
	oval_on_draw on_draw;
} oval_cgpu_device_t;

oval_device_t* oval_create_device(uint16_t width, uint16_t height, oval_on_draw on_draw)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return nullptr;

	SDL_Window* window = SDL_CreateWindow("HelloSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
	if (window == nullptr)
	{
		SDL_Quit();
		return nullptr;
	}

	auto device_cgpu = new oval_cgpu_device_t();
	device_cgpu->window = window;
	device_cgpu->on_draw = on_draw;
	return (oval_device_t*)device_cgpu;
}

void oval_runloop(oval_device_t* device)
{
	auto D = (oval_cgpu_device_t*)device;
	// 获取窗口所包含的表面
	SDL_Surface* screenSurface = SDL_GetWindowSurface(D->window);

	// 将表面填充为蓝色
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 51, 76, 204));

	// 更新表面
	SDL_UpdateWindowSurface(D->window);

	// 窗口循环
	SDL_Event e;
	bool quit = false;
	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
			D->on_draw(device);
		}
	}
}

void oval_free_device(oval_device_t* device)
{
	auto D = (oval_cgpu_device_t*)device;

	// 销毁窗口
	SDL_DestroyWindow(D->window);
	// 退出 SDL
	SDL_Quit();

	delete D;
}

void oval_draw_clear(oval_device_t* device, oval_color_t color)
{
}

void oval_draw_lines(oval_device_t* device, oval_point_t* points, uint32_t count)
{
}

void oval_draw_commit(oval_device_t* device)
{
}
