#ifndef __APP_H_
#define __APP_H_
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Animation.h"
#include "Event.h"

class Texture;
class App : public Event {
   private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Texture* textureYoshi;

    Animation animationYoshi;

   public:
    App();
    int OnExecute();

   public:
    bool OnInit();
    void OnEvent(SDL_Event* event);
    void OnLoop();
    void OnRender();
    void OnCleanup();

   public:
    void OnExit();
};
#endif