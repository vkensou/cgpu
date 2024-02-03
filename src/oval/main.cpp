#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv)
{
	// 初始化 SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "[Error]: SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
    {
		// 定义 SDL 窗口
		SDL_Window* window = SDL_CreateWindow("HelloSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
		if (window == nullptr)
		{
			std::cout << "[Error]: Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
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
		}
		// 销毁窗口
		SDL_DestroyWindow(window);
    }
	// 退出 SDL
	SDL_Quit();
    return 0;
}