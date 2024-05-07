#include <SDL2/SDL.h>
#include "../include/vector2d.h"
#include "../include/rectangle.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Texture* screenTexture = NULL;
SDL_Renderer* renderer = NULL;

bool quit = false;
SDL_Event e;

bool Create()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		window = SDL_CreateWindow("SDL2 Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer == NULL || window == NULL)
		{
			printf("Window or Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}
}

void Update()
{
	while (!quit)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		
		// while (SDL_GetTicks64() < lastTick + 16);
		// float deltaTime = (SDL_GetTicks64() / currentFrame) / 1000.0;
		// lastTick = SDL_GetTicks64();
		
		SDL_UpdateWindowSurface(window);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 0x00, 0xFF);
		SDL_Rect rect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 16, 16 };
		SDL_RenderFillRect(renderer, &rect);

		Rectangle rectangle = 
		{ 
			50, SCREEN_HEIGHT / 2, 
			16, 16, 
			Color::blue,
		};

		rectangle.render(renderer);

		SDL_RenderPresent(renderer);
	}
}

void Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	if(Create())
	{
		Update();
	}

	Destroy();

	return 0;
}