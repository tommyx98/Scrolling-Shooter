#ifndef EXAMREAL_ASSETMANAGER_H
#define EXAMREAL_ASSETMANAGER_H

#include <map>
#include <string>
#include "Texture.h"
#include "Vector2D.h"
#include "./ComponentBasedES/ComponentSystem.h"

class AssetManager{
public:
    AssetManager(EntityManager *m);
    ~AssetManager();

    void AddTexture(std::string key, const char *fileName);
    SDL_Texture* GetTexture(std::string key);

    void CreateBullet(Vector2D position, Vector2D spd, int range, int velocity, int sizeX, int sizeY, float scale, std::string key, std::string entity);

private:
    std::map<std::string, SDL_Texture*> textures;
    EntityManager *entityManager;
};

#endif //EXAMREAL_ASSETMANAGER_H
