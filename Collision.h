#ifndef MAIN_CPP_COLLISION_H
#define MAIN_CPP_COLLISION_H
#include "SDL.h"

class ColliderComponent;

class Collision{
public:
    static bool AABBCollisionCheck(const SDL_Rect &rectangleX, const SDL_Rect &rectangleY);
};

#endif //MAIN_CPP_COLLISION_H
