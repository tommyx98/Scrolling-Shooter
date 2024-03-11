#include "EnemyFactory.h"
#include "stdlib.h"
#include "SDLManager.h"
#include "./ComponentBasedES/AllComponents.h"

extern EntityManager entityManager;

EnemyFactory::EnemyFactory() {}

EnemyFactory::~EnemyFactory() {}

void EnemyFactory::CreateEnemy() {
    int maxWidth =SDL_GetWindowSurface(SDLManager::window)->w;
    float randomXPosition = static_cast<float> (rand() % maxWidth + 0);
    float randomYPosition = static_cast<float> (rand() % 100);
    int randomEnemyType = rand() % 2 + 0;

    auto& enemy(entityManager.AddEntity());

    if(randomEnemyType == 0){
        enemy.AddComponentToEntity<TransformComponent>(randomXPosition, -randomYPosition, 64, 64, 0.5f);
        enemy.AddComponentToEntity<SpriteComponent>("enemy", 2, 1000);
        enemy.AddComponentToEntity<ColliderComponent>("enemy");
        enemy.AddGroupToEntity(SDLManager::ENEMY);
        enemy.AddComponentToEntity<HealthComponent>(20);
        enemy.AddComponentToEntity<EnemyMovementComponent>("enemy");
    }

    else{
        enemy.AddComponentToEntity<TransformComponent>(randomXPosition, -randomYPosition, 64, 64, 0.7);
        enemy.AddComponentToEntity<SpriteComponent>("enemy2", 2, 1000);
        enemy.AddGroupToEntity(SDLManager::ENEMY);
        enemy.AddComponentToEntity<EnemyMovementComponent>("enemy2");
        enemy.AddComponentToEntity<ColliderComponent>("enemy2");
        enemy.AddComponentToEntity<HealthComponent>(30);
    }
}

