#include "vector2d.h"
#include <math.h>

Vector2D Vector2D::operator*(double scalar) const {
    return {x * scalar, y * scalar};
}

Vector2D&  Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D  Vector2D::operator+(const Vector2D& other) {
    *this += other;
    return *this;
}

float Vector2D::magnitude() {
	return sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() {
	double mag = magnitude();
	if (mag != 0) {
		return { x / mag, y / mag };
	}
	else {
		// Return a zero vector if the magnitude is zero
		return { 0.0, 0.0 };
	}
}
