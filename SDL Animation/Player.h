#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "Entity.h"

class CPlayer : public Entity {
   public:
    CPlayer();

    bool OnLoad(SDL_Renderer* renderer, std::string& file, int width, int height, int maxFrames);

    void OnLoop();

    void OnRender();

    void OnCleanup();

    void OnAnimate();

    bool OnCollision(Entity* Entity);
};

#endif