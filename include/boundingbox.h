#pragma once
#include "vector2d.h"

class BoundingBox
{
    public:
        Vector2D center;
        float width;
        float height;

        BoundingBox(Vector2D center, float width, float height);

        float minX();
        float maxX();
        float minY();
        float maxY();

        bool operator[](BoundingBox other);
};