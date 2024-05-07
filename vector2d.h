#pragma once


struct Vector2D
{
    float x;
    float y;
    Vector2D operator*(double scalar) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D operator+(const Vector2D& other);
    float magnitude();
    Vector2D normalize();
};
