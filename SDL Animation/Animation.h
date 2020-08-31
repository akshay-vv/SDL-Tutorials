#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <SDL.h>

class Animation {
   private:
    int currentFrame;
    int frameInc;

   private:
    int frameRate;  //Milliseconds
    long oldTime;

   public:
    int maxFrames;
    bool oscillate;

   public:
    Animation();
    void OnAnimate();

   public:
    void setFrameRate(int rate);
    void setCurrentFrame(int frame);
    int getCurrentFrame();
    void setMaxFrames(int frame);
};

#endif