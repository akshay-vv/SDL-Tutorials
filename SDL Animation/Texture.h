#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>

#include "App.h"

class Texture {
   private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;

   public:
    Texture(SDL_Renderer* renderer);
    Texture(SDL_Renderer* renderer, std::string& file);
    Texture(SDL_Renderer* renderer, std::string file, int red, int green, int blue);
    virtual ~Texture();
    void OnDraw();
    void OnDraw(int destX, int destY, int srcX, int srcY, int srcW, int srcH);
    int getWidth();
    int getHeight();
};

#endif