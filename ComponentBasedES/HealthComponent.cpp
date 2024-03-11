#include "HealthComponent.h"

void HealthComponent::HitChecker() {
    auto &bullets(entityManager.GetGroup(SDLManager::BULLET));
    auto &enemyBullets(entityManager.GetGroup(SDLManager::ENEMYBULLET));
    auto &enemies(entityManager.GetGroup(SDLManager::ENEMY));
    auto &players(entityManager.GetGroup(SDLManager::PLAYER));

    for(auto &e : enemies){
        if(e->EntityHasComponent<ColliderComponent>()){
            SDL_Rect eCollider = e->GetComponentFromEntity<ColliderComponent>().collider;
            for(auto &bu : bullets){
                if(Collision::AABBCollisionCheck(eCollider, bu->GetComponentFromEntity<ColliderComponent>().collider)){
                    e->GetComponentFromEntity<HealthComponent>().TakeDamage();
                    bu->DestroyEntity();
                }
            }

            if (Collision::AABBCollisionCheck(entityManager.GetGroup(SDLManager::PLAYER)[0]->GetComponentFromEntity<ColliderComponent>().collider,
                                              eCollider)) {
                if(!entityManager.GetGroup(SDLManager::PLAYER)[0]->GetComponentFromEntity<InvicibilityComponent>().EntityIsInvicible()) {
                    // bouncing off of colliding object
                    entityManager.GetGroup(
                            SDLManager::PLAYER)[0]->GetComponentFromEntity<TransformComponent>().velocity *
                    -1;
                    entityManager.GetGroup(SDLManager::PLAYER)[0]->GetComponentFromEntity<HealthComponent>().TakeDamage();
                    entityManager.GetGroup(SDLManager::PLAYER)[0]->GetComponentFromEntity<InvicibilityComponent>().SetInvicibility();
                }
            }
        }
    }

    for(auto &p : players){
        if(p->EntityHasComponent<ColliderComponent>()){
            SDL_Rect pCollider = p->GetComponentFromEntity<ColliderComponent>().collider;
            for(auto &eBU : enemyBullets){
                if(Collision::AABBCollisionCheck(pCollider, eBU->GetComponentFromEntity<ColliderComponent>().collider)){
                    if(!p->GetComponentFromEntity<InvicibilityComponent>().EntityIsInvicible()){
                        p->GetComponentFromEntity<HealthComponent>().TakeDamage();
                        eBU->DestroyEntity();
                        p->GetComponentFromEntity<InvicibilityComponent>().SetInvicibility();
                    }
                }
            }
        }
    }
}

// updates score displayed on screen
void HealthComponent::UpdateScore() {
    auto& score = (entityManager.GetGroup(SDLManager::SCORETEXT))[0];
    auto& player = (entityManager.GetGroup(SDLManager::PLAYER))[0];
    std::string baseScoreText = "SCORE: ";
    int scorePlayer = player->GetComponentFromEntity<ScoreTrackerComponent>().GetScore();
    player->GetComponentFromEntity<ScoreTrackerComponent>().SetScore(scorePlayer += 1);
    std::string result = baseScoreText + std::to_string(scorePlayer);
    const char *scoreText = const_cast<char*>(result.c_str());
    score->GetComponentFromEntity<UIComponent>().InitializeText(scoreText);
}

// updates health displayed on screen
void HealthComponent::UpdateHealth() {
    auto& health = (entityManager.GetGroup(SDLManager::HEALTHTEXT))[0];
    auto& player = (entityManager.GetGroup(SDLManager::PLAYER))[0];
    std::string baseHealthText = "HEALTH: ";
    int health2 = player->GetComponentFromEntity<HealthComponent>().GetHealth();
    std::string resultHealth = baseHealthText + std::to_string(health2);
    const char *theHealthText = const_cast<char*>(resultHealth.c_str());
    health->GetComponentFromEntity<UIComponent>().InitializeText(theHealthText);
}
