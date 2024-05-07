#include <SDL2/SDL.h>
#include "../include/vector2d.h"
#include "../include/rectangle.h"
#include "../include/game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool quit = false;
SDL_Event e;

Game game = 
{
	{ 640, 480 },
};

int main(int argc, char* args[])
{
	if(game.create())
	{
		game.update();
	}

	game.destroy();

	return 0;
}