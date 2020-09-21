#include "Texture.h"

#include <SDL_image.h>
#include <string.h>

Texture::Texture(SDL_Renderer* renderer) {
    this->renderer = renderer;
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 640, 640);
    SDL_SetRenderTarget(renderer, texture);
}

Texture::Texture(SDL_Renderer* renderer, std::string& file) {
    this->renderer = renderer;
    texture = IMG_LoadTexture(renderer, file.c_str());
}

// TODO: Replace with Builder
Texture::Texture(SDL_Renderer* renderer, std::string file, int red, int green, int blue) {
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load(file.c_str());
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

void Texture::OnDraw(int destX, int destY, int srcX, int srcY, int srcW, int srcH) {
    SDL_Rect sourceRect;
    sourceRect.x = srcX;
    sourceRect.y = srcY;
    sourceRect.h = srcH;
    sourceRect.w = srcW;

    SDL_Rect destRect;
    destRect.x = destX;
    destRect.y = destY;
    destRect.h = srcH;
    destRect.w = srcW;
    SDL_RenderCopy(renderer, texture, &sourceRect, &destRect);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}
