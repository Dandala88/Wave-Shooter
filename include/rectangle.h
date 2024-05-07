#pragma once
#include "SDL2/SDL.h"
#include "../include/color.h"
#include "../include/vector2d.h"
#include "../include/dimensions.h"

class Rectangle
{
    public:
        Vector2D location;
        Dimensions dimensions;
        Color color;

        Rectangle(Vector2D location, Dimensions dimensions, Color color);

        void render(SDL_Renderer* renderer);
};