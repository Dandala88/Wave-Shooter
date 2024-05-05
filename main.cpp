#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Texture* screenTexture = NULL;
SDL_Renderer* renderer = NULL;

struct Vector2D {
	double x;
	double y;

	Vector2D operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

	Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

Vector2D operator+(Vector2D lhs, const Vector2D& rhs) {
    lhs += rhs;
    return lhs;
}

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
		Vector2D position;
		float width;
		float height;
		float speed;
		Vector2D direction;
		bool invincible = false;
		float iFrames = 1.0;
		float iFramesElapsed = 0;
		SDL_Color color;


		Actor(Vector2D position_val, float width_val, float height_val, float speed_val, SDL_Color color_val) : position(position_val), width(width_val), height(height_val), speed(speed_val), color(color_val) 
		{
			direction = { 0.0, 0.0 };
		}

		void Render()
		{
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect actorRect = { position.x, position.y, width, height };
			SDL_RenderFillRect(renderer, &actorRect);
		}
};

class Character: public Actor
{
	public:
		int health;
		int maxHealth;
		bool dead = false;

		Character(Vector2D position_val, float width_val, float height_val, float speed_val, int maxHealth, SDL_Color color_val) :
		Actor(position_val, width_val, height_val, speed_val, color_val) 
		{
			health = maxHealth;
			color = color_val;
		}

		void Hurt()
		{
			invincible = true;
			--health;
			
			if(health <= 0)
				dead = true;
		}

		virtual void Update(float dt)
		{
			if(invincible)
				iFramesElapsed += dt;
			
			if(iFramesElapsed >= iFrames)
			{
				invincible = false;
				iFramesElapsed = 0;
			}

			if(!dead)
				Render();
		}
};



class Wave: public Actor
{
	public:
		float lifetime = 1.0;
		float lifeElapsed = 0;
		Character* owner;

		Wave(Vector2D position_val, float width_val, float height_val, float speed_val, SDL_Color color_val, Character* owner_val) :
        Actor(position_val, width_val, height_val, speed_val, color_val) 
		{
			owner = owner_val;
		}
};

class Enemy: public Character
{
	public:
		float attackElapsed = 0;
		float attackCooldown = 1.0;
		Enemy(Vector2D position_val, float width_val, float height_val, float speed_val, int maxHealth, SDL_Color color_val) :
		Character(position_val, width_val, height_val, speed_val, maxHealth, color_val) 
		{
			direction = { 1.0, 0.0 };
		}

		void Update(float dt) override 
		{
			Character::Update(dt);

			if (position.x >= SCREEN_WIDTH - width)
				direction.x = -1;
			if (position.x <= 0)
				direction.x = 1;
			position.x += speed * direction.x * dt;
		}

		void AutoAttack(float dt, std::vector<Wave>& waves)
		{
			if(attackElapsed >= attackCooldown && !dead)
			{
				attackElapsed = 0;
				SDL_Color waveColor = color;
				Wave wave({ position.x + (width / 2 - wave.width) , position.y + height + 1 }, 4, 4, 100, waveColor, this);
				wave.direction = { 0.0, 1.0 };
				waves.push_back(wave);
			}
			attackElapsed += dt;
		}
};

bool detectCollision(Actor a, Actor b)
{
	auto a_max_x = a.position.x + a.width;
	auto a_min_x = a.position.x;
	auto a_max_y = a.position.y + a.height;
	auto a_min_y = a.position.y;

	auto b_max_x = b.position.x + b.width;
	auto b_min_x = b.position.x;
	auto b_max_y = b.position.y + b.height;
	auto b_min_y = b.position.y;

	if(a_max_x < b_min_x || a_min_x > b_max_x)
		return false;

	if(a_max_y < b_min_y || a_min_y > b_max_y)
		return false;
	
	return true;
}


bool quit = false;
SDL_Event e;

SDL_Color playerColor { 0x00, 0xFF, 0x00, 0xFF };
Character player({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, 16, 16, 100, 10, playerColor);
std::vector<Wave> waves;

SDL_Color enemyColor { 0xFF, 0x00, 0x00, 0xFF };
Enemy enemy({ SCREEN_WIDTH / 2 , 50 }, 16, 16, 80, 2, enemyColor);
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
			player.position += normalize(input) * player.speed * deltaTime;
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		if (keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_RETURN])
		{
			if (fireCooldownCurrent >= fireCooldown)
			{
				fireCooldownCurrent = 0.0;
				SDL_Color waveColor = { 0x00, 0xFF, 0x00, 0xFF };
				Wave wave({ player.position.x + (player.width / 2 - wave.width / 2) , player.position.y }, 4, 4, 100, waveColor, &player);

				wave.direction = { 0.0, -1.0 };
				waves.push_back(wave);
			}
		}

		auto waveIter = waves.begin();
		while (waveIter != waves.end())
		{
			auto& wave = *waveIter;
			if(wave.lifeElapsed >= wave.lifetime)
				waveIter = waves.erase(waveIter);
			else
			{
				wave.position += normalize(wave.direction) * wave.speed * deltaTime;

				if (detectCollision(wave, enemy) && !enemy.invincible)
				{
					if(wave.owner != &enemy)
					{
						printf("Hit!\n");
						waveIter = waves.erase(waveIter);
						enemy.Hurt();
					}
				}
				else if (detectCollision(wave, player) && !player.invincible)
				{
					if(wave.owner != &player)
					{
						printf("Ouch!\n");
						waveIter = waves.erase(waveIter);
						player.Hurt();
					}
				}
				else
				{
					wave.Render();
					++waveIter;
				}
				wave.lifeElapsed += deltaTime;
			}
		}

		player.Update(deltaTime);
		enemy.Update(deltaTime);
		enemy.AutoAttack(deltaTime, waves);

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

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();

	return 0;
}