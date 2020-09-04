#ifndef _TILE_H_
#define _TILE_H_

#include "Define.h"

enum TileType {
    TILE_TYPE_NONE = 0,
    TILE_TYPE_NORMAL,
    TILE_TYPE_BLOCK
};

class Tile {
   public:
    int tileId;
    int type;

   public:
    Tile();
};
#endif