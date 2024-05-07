#include "ousia.h"
#include <iostream>

Ousia::Ousia(std::string name, Vector2D position, Form* form) : name(name), position(position), form(form) 
{
    form->position = position;
}

void Ousia::Create() {}

void Ousia::Update(float dt) 
{
    std::cout << position.x << std::endl;
    form->position = position;
    form->Render();
    boundingBox.center = position;
}

void Ousia::Destroy() {}

Ousia::~Ousia() {}