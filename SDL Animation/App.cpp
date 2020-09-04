#include "App.h"

#include "Area.h"
#include "Camera.h"
#include "Define.h"
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

    if ((window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, 0)) == NULL) {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (Area::AreaControl.OnLoad(renderer, "maps/1_area.txt") == false) {
        return false;
    }

    return true;
}

void App::OnEvent(SDL_Event* event) {
    Event::OnEvent(event);
}

void App::OnLoop() {
}

void App::OnRender() {
    SDL_RenderClear(renderer);

    Area::AreaControl.OnRender(Camera::CameraControl.getX(), Camera::CameraControl.getY());

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
        case SDLK_UP:
            keyStates[SDLK_UP] = true;
            Camera::CameraControl.OnMove(keyStates);
            break;
        case SDLK_DOWN:
            keyStates[SDLK_DOWN] = true;
            Camera::CameraControl.OnMove(keyStates);
            break;
        case SDLK_LEFT:
            keyStates[SDLK_LEFT] = true;
            Camera::CameraControl.OnMove(keyStates);
            break;
        case SDLK_RIGHT:
            keyStates[SDLK_RIGHT] = true;
            Camera::CameraControl.OnMove(keyStates);
            break;
        default: {
        }
    }
}

void App::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
    switch (sym) {
        case SDLK_UP:
            keyStates[SDLK_UP] = false;
            Camera::CameraControl.OnMove(keyStates);
            break;
        case SDLK_DOWN:
            keyStates[SDLK_DOWN] = false;
            Camera::CameraControl.OnMove(keyStates);
            break;
        case SDLK_LEFT:
            keyStates[SDLK_LEFT] = false;
            Camera::CameraControl.OnMove(keyStates);
            break;
        case SDLK_RIGHT:
            keyStates[SDLK_RIGHT] = false;
            Camera::CameraControl.OnMove(keyStates);
            break;
        default: {
        }
    }
}