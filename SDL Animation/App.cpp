#include "App.h"

#include "Texture.h"

App::App() {
    window = NULL;
    running = true;
    renderer = NULL;
    textureYoshi = NULL;
}

int App::OnExecute() {
    if (!OnInit())
        return -1;

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();

        SDL_Delay(1);  // Breathe
    }

    OnCleanup();

    return 0;
}

bool App::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    if ((window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, 0)) == NULL) {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    textureYoshi = new Texture(renderer, "images/yoshi.bmp");
    animationYoshi.setMaxFrames(8);
    return true;
}

void App::OnEvent(SDL_Event *event) {
    Event::OnEvent(event);
}

void App::OnLoop() {
    animationYoshi.OnAnimate();
}

void App::OnRender() {
    textureYoshi->OnDraw(0, animationYoshi.getCurrentFrame() * 64, 64, 64, 290, 220);
    SDL_RenderPresent(renderer);
}

void App::OnCleanup() {
    delete textureYoshi;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::OnExit() {
    running = false;
}