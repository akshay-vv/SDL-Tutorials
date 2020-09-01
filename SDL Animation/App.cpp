#include "App.h"

#include "Texture.h"

App::App() {
    window = NULL;
    running = true;
    renderer = NULL;
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
    entity1.OnLoad(renderer, "images/yoshi.bmp", 64, 64, 8);
    entity2.OnLoad(renderer, "images/yoshi.bmp", 64, 64, 8);

    entity2.x = 100;
    Entity::entityList.push_back(&entity1);
    Entity::entityList.push_back(&entity2);

    return true;
}

void App::OnEvent(SDL_Event* event) {
    Event::OnEvent(event);
}

void App::OnLoop() {
    for (Entity* e : Entity::entityList) {
        e->OnLoop();
    }
}

void App::OnRender() {
    SDL_RenderClear(renderer);
    for (Entity* e : Entity::entityList) {
        e->OnRender();
    }
    SDL_RenderPresent(renderer);
}

void App::OnCleanup() {
    for (Entity* e : Entity::entityList) {
        if (!e) continue;
        e->OnCleanup();
    }
    Entity::entityList.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::OnExit() {
    running = false;
}