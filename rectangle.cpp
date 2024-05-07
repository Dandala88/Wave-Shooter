#include "rectangle.h"
#include <iostream>

Rectangle::Rectangle(SDL_Renderer *renderer, Vector2D position, float width, float height, SDL_Color color) : Form(renderer, position, width, height) {}

void Rectangle::Render()
{
    std::cout << color.b << std::endl;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { position.x, position.y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}