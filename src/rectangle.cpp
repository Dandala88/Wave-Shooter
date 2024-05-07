#include "../include/rectangle.h"

Rectangle::Rectangle(float x, float y, float w, float h, Color color) : x(x), y(y), w(w), h(h), color(color) {}

void Rectangle::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}