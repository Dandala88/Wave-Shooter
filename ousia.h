#pragma once
#include "vector2d.h"
#include <string>
#include "boundingbox.h"
#include "form.h"

class Ousia
{
    public:
        std::string name;
        Vector2D position;
        Vector2D direction;
        Vector2D velocity;
        Form* form;
        BoundingBox boundingBox {position, form->width, form->height };

        Ousia(std::string name, Vector2D position, Form* form);

        virtual void Create();

        virtual void Update(float dt);

        virtual ~Ousia();

        virtual void Destroy();
};
