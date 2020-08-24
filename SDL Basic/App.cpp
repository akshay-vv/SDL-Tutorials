#include "App.h"

App::App() {
    window = NULL;
    running = true;
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
    }

    OnCleanup();
    
    return 0;
}

bool App::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    if ((window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)) == NULL) {
        return false;
    }

    return true;
}

void App::OnEvent(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }
}

void App::OnLoop() {
}

void App::OnRender() {
}

void App::OnCleanup() {
    SDL_Quit();
}
