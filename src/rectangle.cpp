#include "../include/rectangle.h"

Rectangle::Rectangle(Vector2D location, Dimensions dimensions, Color color) : location(location), dimensions(dimensions), color(color) {}

void Rectangle::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { location.x, location.y, dimensions.w, dimensions.h };
    SDL_RenderFillRect(renderer, &rect);
}