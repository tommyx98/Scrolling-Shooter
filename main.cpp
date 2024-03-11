#define SDL_MAIN_HANDLED
#include <SDL_main.h>
#include <SDL.h>
#include "SDLManager.h"

SDLManager *manager = nullptr;

int main() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    manager = new SDLManager();
    manager->CreateWindow();

    while (manager->ISGameRunning()){
        frameStart = SDL_GetTicks();

        manager->EventHandler();
        manager->Update();
        manager->Render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    manager->Cleaner();

    return 0;
}
