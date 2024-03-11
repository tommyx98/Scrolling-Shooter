#include "Texture.h"

// creates and returns texture from given filename
SDL_Texture *Texture::TextureLoader(const char *fileName){
    SDL_Surface *temporarySurface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(SDLManager::renderer, temporarySurface);
    SDL_FreeSurface(temporarySurface);

    return texture;
}

void Texture::Draw(SDL_Texture *texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle) {
    SDL_RenderCopy(SDLManager::renderer, texture, &sourceRectangle, &destinationRectangle);
}