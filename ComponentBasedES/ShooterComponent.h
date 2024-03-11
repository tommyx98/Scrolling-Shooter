#ifndef EXAMREAL_SHOOTERCOMPONENT_H
#define EXAMREAL_SHOOTERCOMPONENT_H

#include "AllComponents.h"
#include "../SDLManager.h"
#include "../Vector2D.h"

class ShooterComponent : public Component{
public:
    ShooterComponent(int r, int v, Vector2D s){
        range = r;
        velocity = v;
        speed = s;
    }

    ~ShooterComponent(){}

    void ComponentInitializer() override{
        transform = &entity->GetComponentFromEntity<TransformComponent>();
        transform->velocity = speed;
    }

    void ComponentUpdate() override{
        distance += velocity;

        if(distance > range){
            entity->DestroyEntity();
        }

        // dont check for x since bullet are only supposed to move on y axis
        else if(transform->position.y < 0 || transform->position.y > static_cast<float>(SDL_GetWindowSurface(SDLManager::window)->h)){
            entity->DestroyEntity();
        }
    }

private:
    TransformComponent *transform;
    int range = 0;
    int velocity = 0;
    int distance = 0;
    Vector2D speed;
};

#endif //EXAMREAL_SHOOTERCOMPONENT_H
