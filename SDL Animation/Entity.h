#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <string>
#include <vector>

#include "Animation.h"

class Texture;
class Entity {
   public:
    static std::vector<Entity*> entityList;

   protected:
    Animation animControl;
    Texture* textureEntity;

   public:
    float x;
    float y;
    int width;
    int height;
    int animState;

   public:
    Entity();
    virtual ~Entity();

   public:
    virtual bool OnLoad(SDL_Renderer* renderer, std::string file, int width, int height, int maxFrames, int r, int g, int b);
    virtual void OnLoop();
    virtual void OnRender();
    virtual void OnCleanup();
};

#endif