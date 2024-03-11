#ifndef MAIN_CPP_SDLMANAGER_H
#define MAIN_CPP_SDLMANAGER_H
#include <SDL_main.h>
#include <SDL.h>
#include <iostream>
#include "vector"

class ColliderComponent;
class AssetManager;

class SDLManager{
public:
    SDLManager();
    ~SDLManager();

    void CreateWindow();
    void EventHandler();
    void Render();
    void Cleaner();
    void Update();
    bool ISGameRunning();
    void Draw();
    void QuitGame();
    void ResetPlayingStatus();
    void AddPlayer();

    enum Groups : std::size_t {
        PLAYER,
        COLLIDER,
        ENEMY,
        BACKGROUND,
        BULLET,
        ENEMYBULLET,
        HEALTHTEXT,
        SCORETEXT
    };

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static AssetManager *assets;
    static SDL_Window *window;

private:
    bool gameIsRunning;
    bool onGameOverScreen = false;
    void GameOver();
};

#endif //MAIN_CPP_SDLMANAGER_H
