#include "../include/rectangle.h"

Rectangle::Rectangle(Vector2D location, Dimension dimension, Color color) : location(location), dimension(dimension), color(color) {}

void Rectangle::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { location.x, location.y, dimension.w, dimension.h };
    SDL_RenderFillRect(renderer, &rect);
}