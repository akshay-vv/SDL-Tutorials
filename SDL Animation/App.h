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
    void OnKeyDown(SDL_Keycode sym, Uint16 mod);
    void OnKeyUp(SDL_Keycode sym, Uint16 mod);
};
#endif