#ifndef __APP_H_
#define __APP_H_
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Animation.h"
#include "Entity.h"
#include "Event.h"

class Texture;
class App : public Event {
   private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Entity entity1, entity2;

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