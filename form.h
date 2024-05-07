#pragma once
#include "universal.h"
#include "vector2d.h"
#include "SDL2/SDL.h"

class Form: Universal
{
    public:
        SDL_Renderer* renderer;
        Vector2D position;
        float width;
        float height;

        Form(SDL_Renderer *renderer, Vector2D position, float width, float height);

        virtual void Render();
};