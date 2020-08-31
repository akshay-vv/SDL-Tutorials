#ifndef __APP_H_
#define __APP_H_
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Event.h"

class App : public Event {
   private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

   public:
    App();
    int OnExecute();

   public:
    void OnExit();

   public:
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};
#endif