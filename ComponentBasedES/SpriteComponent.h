#ifndef MAIN_CPP_SPRITECOMPONENT_H
#define MAIN_CPP_SPRITECOMPONENT_H

#include "AllComponents.h"
#include "SDL.h"
#include "../Texture.h"
#include "../AssetManager.h"

class SpriteComponent : public Component{
public:
    SpriteComponent() = default;

    SpriteComponent(std::string key){
        SetNewTexture(key);
    }

    SpriteComponent(std::string key, int frames, int speed){
        isAnimated = true;
        numberOfFrames = frames;
        msDelayBetweenFrames = speed;
        SetNewTexture(key);
    }

    ~SpriteComponent(){
        //SDL_DestroyTexture(texture);
    }

    void ComponentInitializer() override{
        // add component to entity if it does not exist, to avoid errors
        if(!entity->EntityHasComponent<TransformComponent>()){
            entity->AddComponentToEntity<TransformComponent>(0, 0);
        }

        transform = &entity->GetComponentFromEntity<TransformComponent>();

        sourceRectangle.x = 0;
        sourceRectangle.y = 0;
        sourceRectangle.w = transform->width;
        sourceRectangle.h = transform->height;
    }

    void ComponentUpdate() override{
        if(isAnimated){
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / msDelayBetweenFrames) % numberOfFrames);
        }

        // casting as int because rectangle is expecting int
        destinationRectangle.x = static_cast<int>(transform->position.x);
        destinationRectangle.y = static_cast<int>(transform->position.y);
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    }

    void ComponentDraw() override{
        Texture::Draw(texture, sourceRectangle, destinationRectangle);
    }

    void SetNewTexture(std::string key){
        texture = SDLManager::assets->GetTexture(key);
    }

    void ChangeAnimatedSprite(std::string key, int frames, int speed){
        SetNewTexture(key);
        numberOfFrames = frames;
        msDelayBetweenFrames = speed;
    }

private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect sourceRectangle, destinationRectangle;
    bool isAnimated = false;
    int numberOfFrames = 0;
    int msDelayBetweenFrames = 100;
};

#endif //MAIN_CPP_SPRITECOMPONENT_H
