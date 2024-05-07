#pragma once
#include "form.h"
#include <SDL2/SDL.h>

class Rectangle : public Form
{
    public:
        SDL_Color color;

        Rectangle(SDL_Renderer *renderer, Vector2D position, float width, float height, SDL_Color color);

        void Render() override;
};