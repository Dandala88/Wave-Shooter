#include "../include/boundingbox.h"

BoundingBox::BoundingBox(Vector2D center, float width, float height) : center(center), width(width), height(height) {}

float BoundingBox::minX()
{
    return center.x - (width / 2);
}

float BoundingBox::maxX()
{
    return center.x + (width / 2);
}

float BoundingBox::minY()
{
    return center.y - (height / 2);
}

float BoundingBox::maxY()
{
    return center.y - (height / 2);
}

bool BoundingBox::operator[](BoundingBox other)
{
	if(maxX() < other.minX() || minX() > other.maxX())
		return false;

	if(maxY() < other.minY() || minY() > other.maxY())
		return false;
	
	return true;
}