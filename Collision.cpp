#include "Collision.h"

bool Collision::AABBCollisionCheck(const SDL_Rect &rectangleX, const SDL_Rect &rectangleY) {
    SDL_Rect *result = new SDL_Rect();
    return SDL_IntersectRect(&rectangleX, &rectangleY, result);

}