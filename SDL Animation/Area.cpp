#include "Area.h"

#include <errno.h>

#include <fstream>
#include <iostream>

#include "Texture.h"

Area Area::AreaControl;

Area::Area() {
    areaSize = 0;
}

bool Area::OnLoad(SDL_Renderer* renderer, std::string file) {
    mapList.clear();
    FILE* areaFile = fopen(file.c_str(), "r");

    if (areaFile == NULL) {
        std::cout << "Failed to open file: " << file << " " << errno;
        return false;
    }

    char tilesetFile[255];
    memset(tilesetFile, 0, 255);
    fscanf(areaFile, "%s\n", tilesetFile);
    std::string tileSetStr(tilesetFile);
    textureTileset = new Texture(renderer, tileSetStr);

    fscanf(areaFile, "%d\n", &areaSize);

    for (int x = 0; x < areaSize; ++x) {
        for (int y = 0; y < areaSize; ++y) {
            char mapFile[255];
            fscanf(areaFile, "%s ", mapFile);

            Map tempMap;
            if (tempMap.OnLoad(mapFile) == false) {
                fclose(areaFile);
                return false;
            }

            tempMap.textureTileset = textureTileset;
            mapList.push_back(tempMap);
        }
        fscanf(areaFile, "\n");
    }
    fclose(areaFile);
    return true;
}

void Area::OnRender(int cameraX, int cameraY) {
    int mapWidth = MAP_WIDTH * TILE_WIDTH;
    int mapHeight = MAP_HEIGHT * TILE_HEIGHT;

    int firstMapId = -cameraX / mapWidth;
    firstMapId += ((-cameraY / mapHeight) * areaSize);

    int visibleWidth = 2;
    int visibleHeight = 2;
    for (int i = 0; i < visibleWidth * visibleHeight; ++i) {
        int id = ((i / visibleWidth) * areaSize) + firstMapId;
        id += (i % visibleHeight);

        if (id >= 0 && id < mapList.size()) {
            int x = ((id % areaSize) * mapWidth) + cameraX;
            int y = ((id / areaSize) * mapHeight) + cameraY;
            mapList[id].OnRender(x, y);
        }
    }
}

Map* Area::GetMap(int X, int Y) {
    int MapWidth = MAP_WIDTH * TILE_WIDTH;
    int MapHeight = MAP_HEIGHT * TILE_HEIGHT;

    int ID = X / MapWidth;
    ID = ID + ((Y / MapHeight) * areaSize);

    if (ID < 0 || ID >= mapList.size()) {
        return NULL;
    }

    return &mapList[ID];
}

Tile* Area::GetTile(int X, int Y) {
    int MapWidth = MAP_WIDTH * TILE_WIDTH;
    int MapHeight = MAP_HEIGHT * TILE_HEIGHT;

    Map* Map = GetMap(X, Y);

    if (Map == NULL) return NULL;

    X = X % MapWidth;
    Y = Y % MapHeight;

    return Map->GetTile(X, Y);
}

void Area::OnCleanup() {
    if (textureTileset)
        delete textureTileset;
    mapList.clear();
}