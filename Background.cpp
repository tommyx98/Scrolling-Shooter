#include "Background.h"
#include <fstream>
#include "SDLManager.h"
#include "./ComponentBasedES/AllComponents.h"

extern EntityManager entityManager;

Background::Background() {}

Background::~Background() {}

// loops trough background text file and adds tiles
void Background::LoadBackground(std::string fileName, int sizeX, int sizeY) {
    char tile;
    std::fstream file;
    file.open(fileName);

    for(int y = 0; y < sizeY; y++){
        for(int x = 0; x < sizeX; x++){
            file.get(tile);

            if(tile == '1'){
                AddColliderTile(atoi(&tile), x * 16, y * 16);
                file.ignore();
            }

            else {

                // conversion because tile ids are specified as int but read as chars from file
                AddTile(atoi(&tile), x * 16, y * 16);
                file.ignore();
            }
        }
    }
    file.close();
}

void Background::AddTile(int tileID, int xPosition, int yPosition) {
    auto &tile(entityManager.AddEntity());
    tile.AddComponentToEntity<TileComponent>(xPosition, yPosition, 16, 16, tileID);
    tile.AddGroupToEntity(SDLManager::BACKGROUND);
}

void Background::AddColliderTile(int tileID, int xPosition, int yPosition) {
    auto &tile(entityManager.AddEntity());
    tile.AddComponentToEntity<TileComponent>(xPosition, yPosition, 16, 16, tileID);
    tile.AddComponentToEntity<ColliderComponent>("barricade");
    tile.AddGroupToEntity(SDLManager::COLLIDER);
}
