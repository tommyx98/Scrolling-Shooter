#ifndef EXAMREAL_UICOMPONENT_H
#define EXAMREAL_UICOMPONENT_H

#include "AllComponents.h"
#include "SDL_ttf.h"

class UIComponent : public Component{
public:
     UIComponent(int xPosition, int yPosition){
         position.x = xPosition;
         position.y = yPosition;
     }

     ~UIComponent(){}

     void InitializeText(const char *text){
         TTF_Font *font = TTF_OpenFont("../font/INVASION2000.TTF", 20);
         SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
         texture = SDL_CreateTextureFromSurface(SDLManager::renderer, surface);
         SDL_FreeSurface(surface);
         SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
         TTF_CloseFont(font);
     }

     void ComponentDraw() override{
         SDL_RenderCopy(SDLManager::renderer, texture, nullptr, &position);
     }

private:
     SDL_Color color = {255, 255, 255};
     SDL_Rect position;
     SDL_Texture *texture;
};

#endif //EXAMREAL_UICOMPONENT_H
