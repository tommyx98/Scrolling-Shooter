#ifndef EXAMREAL_ENEMYMOVEMENTCOMPONENT_H
#define EXAMREAL_ENEMYMOVEMENTCOMPONENT_H

#include "AllComponents.h"
#include "../Vector2D.h"

class EnemyMovementComponent : public Component{
public:

    EnemyMovementComponent(std::string eType){
        enemyType = eType;
    }

    ~EnemyMovementComponent(){}

    void ComponentInitializer() override{
        xDirection = rand() % 2 + 0;
        transform = &entity->GetComponentFromEntity<TransformComponent>();
        startTime = SDL_GetTicks() / 1000;
        maxWidth = static_cast<float> (SDL_GetWindowSurface(SDLManager::window)->w);
        maxHeight = static_cast<float>(SDL_GetWindowSurface(SDLManager::window)->h);
    }

    void ComponentUpdate() override{
        currentTime = SDL_GetTicks() / 1000;

        transform->position.y += 0.5;

        if(currentTime - startTime > 1){
            xDirection = rand() % 2 + 0;
            startTime = SDL_GetTicks() / 1000;

            if(enemyType == "enemy"){
                SDLManager::assets->CreateBullet(Vector2D(transform->position.x + 22, transform->position.y + 5), Vector2D(0, 2), 700, 2, 16, 16, 0.5, "bullet_enemy", "enemy");
                SDLManager::assets->CreateBullet(Vector2D(transform->position.x + 7, transform->position.y + 5), Vector2D(0, 2), 700, 2, 16, 16, 0.5, "bullet_enemy", "enemy");
            }

            if(enemyType == "enemy2"){
                SDLManager::assets->CreateBullet(Vector2D(transform->position.x + 15, transform->position.y + 20), Vector2D(0, 2), 700, 2, 32, 32, 0.5, "bullet_enemy2", "enemy");
            }
        }
        float currentXPosition = transform->position.x;
        float nextXPosition = currentXPosition + xSway[xDirection];

        // makes sure enemy does not move out of map sideways
        if(nextXPosition < 0){
            xDirection = 1;
        }

        if(nextXPosition >= maxWidth - 40){
            xDirection = 0;
        }

        transform->position.x += xSway[xDirection];

        if(transform->position.y > maxHeight){
            entity->DestroyEntity();
        }
    }

private:
    int xSway [2] = {-1, 1};
    TransformComponent *transform;
    double startTime;
    double currentTime = 0;
    int xDirection;
    std::string enemyType;
    float maxWidth;
    float maxHeight;
};

#endif //EXAMREAL_ENEMYMOVEMENTCOMPONENT_H
