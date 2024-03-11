#ifndef EXAMREAL_INVICIBILITYCOMPONENT_H
#define EXAMREAL_INVICIBILITYCOMPONENT_H

#include "AllComponents.h"

class InvicibilityComponent : public Component{
public:
    InvicibilityComponent(){}

    ~InvicibilityComponent(){}

    bool EntityIsInvicible(){
        return isInvicible;
    }

    void SetInvicibility(){
        isInvicible = true;
    }

    // checks if player is invincible and changes sprite accordingly
    void ComponentUpdate() override{
        if(isInvicible){
            if(!invicibleSprite){
                player->GetComponentFromEntity<SpriteComponent>().ChangeAnimatedSprite("player_invicible", 2, 100);
                invicibleSprite = true;
                startTime = SDL_GetTicks() / 1000;
            }

            currentTime = SDL_GetTicks() / 1000;

            if(currentTime - startTime > 1){
                isInvicible = false;
                startTime = SDL_GetTicks() / 1000;
                player->GetComponentFromEntity<SpriteComponent>().ChangeAnimatedSprite("player", 2, 1000);
                invicibleSprite = false;
            }
        }
    }

private:
    bool isInvicible = false;
    double startTime;
    double currentTime = 0;
    Entity *player = (entityManager.GetGroup(SDLManager::PLAYER))[0];
    bool invicibleSprite = false;
};

#endif //EXAMREAL_INVICIBILITYCOMPONENT_H
