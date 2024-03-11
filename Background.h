#ifndef MAIN_CPP_BACKGROUND_H
#define MAIN_CPP_BACKGROUND_H

#include <string>

class Background {
public:
    Background();
    ~Background();

    void LoadBackground(std::string fileName, int sizeX, int sizeY);
    void AddTile(int tileID, int xPosition, int yPosition);
    void AddColliderTile(int tileID, int xPosition, int yPosition);
};


#endif //MAIN_CPP_BACKGROUND_H
