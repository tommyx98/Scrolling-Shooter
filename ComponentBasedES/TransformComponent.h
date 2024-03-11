#ifndef MAIN_CPP_TRANSFORMCOMPONENT_H
#define MAIN_CPP_TRANSFORMCOMPONENT_H

#include "AllComponents.h"
#include "../Vector2D.h"

struct TransformComponent : public Component{
    Vector2D position;
    Vector2D velocity;

    int height = 64;
    int width = 64;
    float scale = 1;

    int speed = 3;

    TransformComponent(float x, float y){
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, int h, int w, float s){
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = s;
    }

    void ComponentInitializer() override{
        velocity.x = 0;
        velocity.y = 0;
    }

    void ComponentUpdate() override{
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};

#endif //MAIN_CPP_TRANSFORMCOMPONENT_H
