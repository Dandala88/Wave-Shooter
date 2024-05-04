#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Texture* screenTexture = NULL;
SDL_Renderer* renderer = NULL;

struct Vector2D {
	double x;
	double y;
};

double magnitude(const Vector2D& vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Vector2D normalize(const Vector2D& vec) {
	double mag = magnitude(vec);
	if (mag != 0) {
		return { vec.x / mag, vec.y / mag };
	}
	else {
		// Return a zero vector if the magnitude is zero
		return { 0.0, 0.0 };
	}
}

class Actor
{
	public:
		float x;
		float y;
		float speed;
		float direction = 1;

		Actor(float x_val, float y_val, float speed_val, float direction_val) : x(x_val), y(y_val), speed(speed_val), direction(direction_val) {}
};

class Wave: public Actor
{
	public:
		Vector2D initialDirection;

		Wave(float x_val, float y_val, float speed_val, float direction_val) :
        Actor(x_val, y_val, speed_val, direction_val) {}
};


bool quit = false;
SDL_Event e;

Actor player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 1);
std::vector<Wave> waves;

Actor enemy(SCREEN_WIDTH / 2 , 1, 100, 1);
std::vector<SDL_Rect> eWaves;

int currentFrame = 1;
Uint64 lastTick = SDL_GetTicks64();

float fireCooldown = 0.25;
float fireCooldownCurrent = fireCooldown;

void Update()
{
	while (!quit)
	{
		while (SDL_GetTicks64() < lastTick + 16);
		float deltaTime = (SDL_GetTicks64() / currentFrame) / 1000.0;
		lastTick = SDL_GetTicks64();
		SDL_UpdateWindowSurface(window);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		const Uint8* keyState = SDL_GetKeyboardState(NULL);

		Vector2D input = { 0.0, 0.0 };
		bool inputMade = false;
		if (keyState[SDL_SCANCODE_W])
		{
			input.y = -1.0;
			inputMade = true;
		}

		if (keyState[SDL_SCANCODE_S])
		{
			input.y = 1.0;
			inputMade = true;
		}

		if (keyState[SDL_SCANCODE_A])
		{
			input.x = -1.0;
			inputMade = true;
		}

		if (keyState[SDL_SCANCODE_D])
		{
			input.x = 1.0;
			inputMade = true;
		}

		if (inputMade)
		{
			player.y += normalize(input).y * player.speed * deltaTime;
			player.x += normalize(input).x * player.speed * deltaTime;
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_Rect playerRect = { player.x, player.y, 16, 16 };
		SDL_RenderFillRect(renderer, &playerRect);

		if (keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_RETURN])
		{
			if (fireCooldownCurrent >= fireCooldown)
			{
				fireCooldownCurrent = 0.0;
				Wave wave(player.x , player.y - 6, 100, 1);
				wave.initialDirection = {0.0, -1.0 };
				waves.push_back(wave);
			}
		}

		for (auto& wave : waves)
		{
			wave.y += wave.speed * normalize(wave.initialDirection).y * deltaTime;
			wave.x += wave.speed * normalize(wave.initialDirection).x * deltaTime;
			SDL_Rect waveRect = { wave.x , wave.y - 6, 4, 4 };
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &waveRect);
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_Rect enemyRect = { enemy.x, enemy.y, 16, 16 };
		SDL_RenderFillRect(renderer, &enemyRect);

		if (enemy.x >= SCREEN_WIDTH - 16)
			enemy.direction = -1;
		if (enemy.x <= 0)
			enemy.direction = 1;
		enemy.x += enemy.speed * enemy.direction * deltaTime;

		SDL_RenderPresent(renderer);

		fireCooldownCurrent += deltaTime;
		currentFrame++;
	}
}

int main(int argc, char* args[])
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL2 Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer == NULL || window == NULL)
		{
			printf("Window or Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			Update();
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}