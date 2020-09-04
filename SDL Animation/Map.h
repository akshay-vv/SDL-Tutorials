#ifndef _MAP_H_
#define _MAP_H_
#include <string>
#include <vector>

#include "Tile.h"
class Texture;
class Map {
   public:
    Texture* textureTileset;

   private:
    std::vector<Tile> tileList;

   public:
    Map();

   public:
    bool OnLoad(std::string file);
    void OnRender(int mapX, int mapY);
};

#endif