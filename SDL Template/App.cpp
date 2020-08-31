#include "App.h"

#include "Event.h"
#include "Texture.h"

App::App() {
    currentPlayer = 0;
    running = true;
    window = NULL;
    renderer = NULL;
    gridTexture = NULL;
    xTexture = NULL;
    oTexture = NULL;
}

int App::OnExecute() {
    if (!OnInit())
        return -1;

    while (running) {
        OnEvent();
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

    window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_X, WINDOW_Y, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    gridTexture = new Texture(renderer, "images/grid.bmp");
    xTexture = new Texture(renderer, "images/x.bmp", 255, 0, 255);
    oTexture = new Texture(renderer, "images/o.bmp", 255, 0, 255);

    Reset();

    return true;
}

void App::OnEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        Event::OnEvent(&event);
    }
}

void App::OnLoop() {
}

void App::OnRender() {
    SDL_RenderClear(renderer);
    RenderGrid();
    SDL_RenderPresent(renderer);
}

void App::OnCleanup() {
    delete gridTexture;
    delete oTexture;
    delete xTexture;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::OnLButtonDown(int mX, int mY) {
    int id = mX / 200;
    id += ((mY / 200) * 3);

    if (grid[id] != App::NONE)
        return;

    if (currentPlayer == 0) {
        grid[id] = App::X;
        currentPlayer = 1;
    } else {
        grid[id] = App::O;
        currentPlayer = 0;
    }
}

void App::OnRButtonDown(int mX, int mY) {
    Reset();
}

void App::OnExit() {
    running = false;
}

void App::Reset() {
    memset(grid, App::NONE, sizeof(int) * 9);
}

void App::SetCell(int id, int type) {
    if (type < 0 || type > App::O) return;
    if (id < 0 || id > 9) return;

    grid[id] = type;
}

void App::RenderGrid() {
    gridTexture->OnDraw();

    for (int i = 0; i < 9; ++i) {
        int x = (i % 3) * 200;
        int y = (i / 3) * 200;

        if (grid[i] == App::X) {
            xTexture->OnDraw(x, y, 200, 200);
        } else if (grid[i] == App::O) {
            oTexture->OnDraw(x, y, 200, 200);
        }
    }
}