#ifndef _AREA_H_
#define _AREA_H
#include <SDL.h>

#include "Map.h"
class Area {
   public:
    static Area AreaControl;

   public:
    std::vector<Map> mapList;

   private:
    int areaSize;
    Texture* textureTileset;

   public:
    Area();
    bool OnLoad(SDL_Renderer* renderer, std::string file);
    void OnRender(int cameraX, int cameraY);
    void OnCleanup();
};

#endif