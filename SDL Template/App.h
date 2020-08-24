#ifndef __APP_H_
#define __APP_H_
#define SDL_MAIN_HANDLED
#include <SDL.h>

class App
{
private:
    bool running;
    SDL_Window* window;

public:
    App();
    int OnExecute();

public:
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};
#endif