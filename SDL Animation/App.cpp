#include "App.h"

#include <stdio.h>

#include "Area.h"
#include "Camera.h"
#include "Define.h"
#include "FPS.h"
#include "Texture.h"

App::App() {
    window = NULL;
    running = true;
    renderer = NULL;
    OldTime = LastTime = NumFrames = Frames = time = 0;
    SpeedFactor = 0.0f;
    methodCalls = 0ll;
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

        if (SDL_GetTicks() > time + 1000) {
            time = SDL_GetTicks();
            printf("Calls %lld Frames %d  NumFrames %d Speed %f\n", methodCalls, Frames, NumFrames, SpeedFactor);
            methodCalls = 0;
        }
        SDL_Delay(1);  // Breathe
    }

    OnCleanup();

    return 0;
}

bool App::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, 0)) == NULL) {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (Area::AreaControl.OnLoad(renderer, "maps/1_area.txt") == false) {
        return false;
    }

    std::string yoshiImage("images/yoshi.png");
    if (player1.OnLoad(renderer, yoshiImage, 64, 64, 8) == false) {
        return false;
    }

    if (player2.OnLoad(renderer, yoshiImage, 64, 64, 8) == false) {
        return false;
    }

    player2.x = 100;

    Entity::entityList.push_back(&player1);
    Entity::entityList.push_back(&player2);

    Camera::CameraControl.targetMode = TARGET_MODE_CENTER;
    Camera::CameraControl.setTarget(&player1.x, &player1.y);

    return true;
}

void App::OnEvent(SDL_Event* event) {
    Event::OnEvent(event);
}

void App::OnLoop() {
    FPS::FPSControl.onLoop();
    for (auto entity : Entity::entityList) {
        if (entity == NULL) continue;
        entity->OnLoop();
    }
    FPS::FPSControl.onLoop();
}

void App::OnRender() {
    SDL_RenderClear(renderer);

    Area::AreaControl.OnRender(-Camera::CameraControl.getX(), -Camera::CameraControl.getY());
    for (auto entity : Entity::entityList) {
        if (entity == NULL) continue;
        entity->OnRender();
    }

    SDL_RenderPresent(renderer);
}

void App::OnCleanup() {
    Area::AreaControl.OnCleanup();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::OnExit() {
    running = false;
}

void App::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
    switch (sym) {
        case SDLK_LEFT: {
            player1.moveLeft = true;
            break;
        }

        case SDLK_RIGHT: {
            player1.moveRight = true;
            break;
        }

        default: {
        }
    }
}

void App::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
    switch (sym) {
        case SDLK_LEFT: {
            player1.moveLeft = false;
            break;
        }

        case SDLK_RIGHT: {
            player1.moveRight = false;
            break;
        }

        default: {
        }
    }
}