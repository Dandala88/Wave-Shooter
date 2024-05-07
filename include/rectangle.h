#pragma once
#include "SDL2/SDL.h"
#include "../include/color.h"
#include "../include/vector2d.h"
#include "../include/dimension.h"

class Rectangle
{
    public:
        Vector2D location;
        Dimension dimension;
        Color color;

        Rectangle(Vector2D location, Dimension dimension, Color color);

        void render(SDL_Renderer* renderer);
};