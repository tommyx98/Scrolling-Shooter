#ifndef MAIN_CPP_INPUTMANAGERCOMPONENT_H
#define MAIN_CPP_INPUTMANAGERCOMPONENT_H

#include "../SDLManager.h"
#include "AllComponents.h"

extern EntityManager entityManager;
extern SDLManager manager;

class InputManagerComponent : public Component{
public:
    TransformComponent *transform;

    void ComponentInitializer() override{
        // add component to entity if it does not exist, to avoid errors
        if(!entity->EntityHasComponent<TransformComponent>()){
            entity->AddComponentToEntity<TransformComponent>(0, 0);
        }
        transform = &entity->GetComponentFromEntity<TransformComponent>();
    }

    void ComponentUpdate() override{
        if(SDLManager::event.type == SDL_KEYDOWN){
            switch (SDLManager::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = -1;
                    break;

                case SDLK_a:
                    transform->velocity.x = -1;
                    break;

                case SDLK_d:
                    transform->velocity.x = 1;
                    break;

                case SDLK_s:
                    transform->velocity.y = 1;
                    break;

                case SDLK_SPACE: {
                    if(!entityManager.GetGroup(SDLManager::PLAYER).empty()){
                        Entity *player = entityManager.GetGroup(SDLManager::PLAYER)[0];
                        Vector2D playerPosition = player->GetComponentFromEntity<TransformComponent>().position;
                        SDLManager::assets->CreateBullet(Vector2D(playerPosition.x + 7, playerPosition.y), Vector2D(0, -2), 700, 2, 16, 16, 0.5, "bullet", "player");
                        SDLManager::assets->CreateBullet(Vector2D(playerPosition.x + 22, playerPosition.y), Vector2D(0, -2), 700, 2, 16, 16, 0.5, "bullet", "player");
                    }
                    break;
                }

                case SDLK_x:{
                    if(entityManager.GetGroup(SDLManager::PLAYER).empty()){
                        entity->DestroyEntity();
                        manager.ResetPlayingStatus();
                    }
                    break;
                }

                default:
                    break;
            }
        }

        // when key is released set value to 0 to stop moving
        if(SDLManager::event.type == SDL_KEYUP){
            switch (SDLManager::event.key.keysym.sym) {
                case SDLK_w:
                    transform->velocity.y = 0;
                    break;

                case SDLK_a:
                    transform->velocity.x = 0;
                    break;

                case SDLK_d:
                    transform->velocity.x = 0;
                    break;

                case SDLK_s:
                    transform->velocity.y = 0;
                    break;

                default:
                    break;
            }
        }
    }
};

#endif //MAIN_CPP_INPUTMANAGERCOMPONENT_H
