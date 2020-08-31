#include "Texture.h"

#include <string.h>

Texture::Texture(SDL_Renderer* renderer) {
    this->renderer = renderer;
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 640, 640);
    SDL_SetRenderTarget(renderer, texture);
}

Texture::Texture(SDL_Renderer* renderer, std::string file) {
    this->renderer = renderer;
    SDL_Surface* surface = SDL_LoadBMP(file.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

// TODO: Replace with Builder
Texture::Texture(SDL_Renderer* renderer, std::string file, int red, int green, int blue) {
    this->renderer = renderer;
    SDL_Surface* surface = SDL_LoadBMP(file.c_str());
    SDL_SetColorKey(surface, SDL_TRUE | SDL_RLEACCEL, SDL_MapRGB(surface->format, red, green, blue));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

void Texture::OnDraw() {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void Texture::OnDraw(int x, int y, int h, int w, int destX, int destY) {
    SDL_Rect sourceRect;
    sourceRect.x = x;
    sourceRect.y = y;
    sourceRect.h = h;
    sourceRect.w = w;

    SDL_Rect destRect;
    destRect.x = destX;
    destRect.y = destY;
    destRect.h = h;
    destRect.w = w;
    SDL_RenderCopy(renderer, texture, &sourceRect, &destRect);
}