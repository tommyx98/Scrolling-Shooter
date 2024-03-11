#ifndef EXAMREAL_TILECOMPONENT_H
#define EXAMREAL_TILECOMPONENT_H

#include "ComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    SDL_Rect tileRectangle;
    int tileID;
    std::string key;

    TileComponent() = default;

    TileComponent(int xPosition, int yPosition, int width, int height, int id){
        tileRectangle.x = xPosition;
        tileRectangle.y = yPosition;
        tileRectangle.w = width;
        tileRectangle.h = height;
        tileID = id;

        switch (tileID) {
            case 0:
                key = "water";
                SDLManager::assets->AddTexture("water", "../images/water.png");
                break;

            case 1:
                key = "barricade";
                SDLManager::assets->AddTexture("barricade", "../images/end.png");
                break;

            default:
                break;
        }
    }

    void ComponentInitializer() override{
        entity->AddComponentToEntity<TransformComponent>(static_cast<float> (tileRectangle.x),static_cast<float> (tileRectangle.y), tileRectangle.w, tileRectangle.h, 1);
        transform = &entity->GetComponentFromEntity<TransformComponent>();

        entity->AddComponentToEntity<SpriteComponent>(key);
        sprite = &entity->GetComponentFromEntity<SpriteComponent>();
    }
};

#endif //EXAMREAL_TILECOMPONENT_H
