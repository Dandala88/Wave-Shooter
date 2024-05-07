#include "../include/game.h"

bool Game::create()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		window = SDL_CreateWindow("SDL2 Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensions.w, dimensions.h, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer == NULL || window == NULL)
		{
			printf("Window or Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
	}
}

void Game::update()
{
    while (alive)
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
				alive = false;
			}
		}

		//This is just the test render for now, I don't know if I want this in the game class. As mentioned in the header file, I believe this should be a list of entities that have all the same hooks that can be called. This keeps the implementations of the individual entities fully separate. Remember: create, input, update, render, destroy
		// Rectangle rectangle = 
		// { 
		// 	{ game.dimensions.w / 2, game.dimensions.h / 2 }, 
		// 	{ 16, 16 }, 
		// 	Color::blue,
		// };

		// rectangle.render(game.renderer);

		SDL_RenderPresent(renderer);
	}
}

void Game::destroy()
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
}