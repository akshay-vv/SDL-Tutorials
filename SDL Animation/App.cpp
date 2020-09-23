#include "App.h"

#include <stdio.h>

#include "Area.h"
#include "Camera.h"
#include "Define.h"
#include "FPS.h"
#include "SoundBank.h"
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
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
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

    if ((soundA = CSoundBank::SoundControl.OnLoad("audio/sounda.wav")) == -1) {
        return false;
    }

    if ((soundB = CSoundBank::SoundControl.OnLoad("audio/soundb.wav")) == -1) {
        return false;
    }

    // player2.x = 100;
    player1.x = 0;
    player1.y = 0;
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

    for (int i = 0; i < EntityCol::EntityColList.size(); i++) {
        Entity* entityA = EntityCol::EntityColList[i].entityA;
        Entity* entityB = EntityCol::EntityColList[i].entityB;

        if (entityA == NULL || entityB == NULL) continue;

        if (entityA->OnCollision(entityB)) {
            entityB->OnCollision(entityA);
        }
    }

    EntityCol::EntityColList.clear();
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
    CSoundBank::SoundControl.OnCleanup();
    Mix_CloseAudio();
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

        case SDLK_SPACE: {
            if (player1.jump()) {
                CSoundBank::SoundControl.Play(soundA);
            }
            break;
        }

        case SDLK_1: {
            CSoundBank::SoundControl.Play(soundA);
            break;
        }

        case SDLK_RCTRL: {
            CSoundBank::SoundControl.Play(soundB);
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