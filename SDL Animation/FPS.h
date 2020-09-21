#ifndef _FPS_H_
#define _FPS_H_

#include <SDL.h>

class FPS {
   public:
    static FPS FPSControl;

   private:
    int oldTime;
    int lastTime;

    float speedFactor;

    int numFrames;
    int frames;

   public:
    FPS();

    void onLoop();

   public:
    int getFPS();

    float getSpeedFactor();
};

#endif