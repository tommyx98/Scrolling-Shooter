#include "AssetManager.h"
#include "./ComponentBasedES/AllComponents.h"

AssetManager::AssetManager(EntityManager *m) {
    entityManager = m;
}

AssetManager::~AssetManager() {}

void AssetManager::AddTexture(std::string key, const char *fileName) {
    textures.emplace(key, Texture::TextureLoader(fileName));
}

SDL_Texture *AssetManager::GetTexture(std::string key) {
    return textures[key];
}

void AssetManager::CreateBullet(Vector2D position, Vector2D spd, int range, int velocity, int sizeX, int sizeY, float scale, std::string key, std::string entity) {
    auto &bullet(entityManager->AddEntity());
    bullet.AddComponentToEntity<TransformComponent>(position.x, position.y, sizeX, sizeY, scale);
    bullet.AddComponentToEntity<SpriteComponent>(key);
    bullet.AddComponentToEntity<ShooterComponent>(range, velocity, spd);
    bullet.AddComponentToEntity<ColliderComponent>("bullet");

    if(entity == "player"){
        bullet.AddGroupToEntity(SDLManager::BULLET);
    }

    if(entity == "enemy"){
        bullet.AddGroupToEntity(SDLManager::ENEMYBULLET);
    }
}
