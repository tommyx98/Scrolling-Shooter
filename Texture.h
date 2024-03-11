#ifndef MAIN_CPP_TEXTURE_H
#define MAIN_CPP_TEXTURE_H
#include <SDL_image.h>
#include "SDLManager.h"

class Texture {
public:
    static SDL_Texture *TextureLoader(const char *fileName);
    static void Draw(SDL_Texture *texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle);
};


#endif //MAIN_CPP_TEXTURE_H
