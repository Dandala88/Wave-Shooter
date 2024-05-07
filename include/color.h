#pragma once
#include "SDL2/SDL.h"

class Color
{
    public:
        int r;
        int g;
        int b;
        int a;

        Color(int r, int g, int b, int a);

        static Color red;
        static Color green;
        static Color blue;
};