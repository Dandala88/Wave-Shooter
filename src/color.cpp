#include "../include/color.h"

Color::Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

Color Color::red = { 255, 0, 0, 255 };

Color Color::green = { 0, 255, 0, 255 };

Color Color::blue = { 0, 0, 255, 255 };