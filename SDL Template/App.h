#ifndef __APP_H_
#define __APP_H_
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Event.h"

class Texture;
class App : public Event {
   private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Texture* gridTexture;
    Texture* xTexture;
    Texture* oTexture;

   private:
    int currentPlayer;
    int grid[9];
    enum {
        NONE = 0,
        X,
        O
    } GridType;

   public:
    static const int WINDOW_X = 600;
    static const int WINDOW_Y = 600;

    App();
    int OnExecute();
    void Reset();
    void SetCell(int id, int type);
    void RenderGrid();

   public:
    bool OnInit();
    void OnEvent();
    void OnLoop();
    void OnRender();
    void OnCleanup();
    void OnExit();

    void OnLButtonDown(int mX, int mY);
    void OnRButtonDown(int mX, int mY);
};
#endif