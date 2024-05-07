#pragma once
#include "SDL2/SDL.h"
#include "../include/color.h"

class Rectangle
{
    public:
        float x;
        float y;
        float w;
        float h;
        Color color;

        Rectangle(float x, float y, float width, float height, Color color);

        void render(SDL_Renderer* renderer);
};