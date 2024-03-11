#ifndef EXAMREAL_HEALTHCOMPONENT_H
#define EXAMREAL_HEALTHCOMPONENT_H

#include "AllComponents.h"
#include "../Collision.h"

class HealthComponent : public Component{
public:
    HealthComponent(int hp){
        health = hp;
    }

    ~HealthComponent(){}

    void ComponentUpdate() override{
        HitChecker();

        if(health <= 0){
            if(entity->EntityHasGroup(SDLManager::ENEMY)){
                UpdateScore();
            }
            entity->DestroyEntity();
        }
    }

    int GetHealth(){
        return health;
    }

private:
    int health = 0;

    // declared in cpp to allow use of collision
    void HitChecker();

    void UpdateScore();

    void UpdateHealth();

    void TakeDamage(){
        health --;

        if(entity->EntityHasGroup(SDLManager::PLAYER)){
            UpdateHealth();
        }
    }
};

#endif //EXAMREAL_HEALTHCOMPONENT_H
