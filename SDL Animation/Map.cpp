#include "Map.h"

#include "Texture.h"

Map::Map() {
    textureTileset = NULL;
}

bool Map::OnLoad(std::string file) {
    tileList.clear();

    FILE* mapFile = fopen(file.c_str(), "r");
    if (mapFile == NULL) return false;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            Tile tile;
            fscanf(mapFile, "%d:%d", &tile.tileId, &tile.type);
            tileList.push_back(tile);
        }
        fscanf(mapFile, "\n");
    }
    fclose(mapFile);
    return true;
}

void Map::OnRender(int mapX, int mapY) {
    if (textureTileset == NULL) return;

    int tilesWidth = textureTileset->getWidth() / TILE_WIDTH;
    int tilesHeight = textureTileset->getHeight() / TILE_HEIGHT;
    int id = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (tileList[id].type != TILE_TYPE_NONE) {
                // tx and ty is this tiles offset with respect to the map
                int tx = mapX + (x * TILE_WIDTH);
                int ty = mapY + (y * TILE_HEIGHT);

                // tileSetX and tileSetY are the coordinates within tiles.png for tileId
                int tileSetX = (tileList[id].tileId % tilesWidth) * TILE_WIDTH;
                int tileSetY = (tileList[id].tileId / tilesWidth) * TILE_HEIGHT;

                textureTileset->OnDraw(tx, ty, tileSetX, tileSetY, TILE_WIDTH, TILE_HEIGHT);
            }
            ++id;
        }
    }
}