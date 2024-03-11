#ifndef MAIN_CPP_COLLIDERCOMPONENT_H
#define MAIN_CPP_COLLIDERCOMPONENT_H

#include "AllComponents.h"
#include "../Texture.h"

class ColliderComponent : public Component{
public:
    SDL_Rect collider;
    std::string tag;
    TransformComponent *transform;

    ColliderComponent(std::string t){
        tag = t;
    }

    void ComponentInitializer() override{
        // add component to entity if it does not exist, to avoid errors
        if(!entity->EntityHasComponent<TransformComponent>()){
            entity->AddComponentToEntity<TransformComponent>(0, 0);
        }

        transform = &entity->GetComponentFromEntity<TransformComponent>();
    }

    void ComponentUpdate() override{
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }

};

#endif //MAIN_CPP_COLLIDERCOMPONENT_H
