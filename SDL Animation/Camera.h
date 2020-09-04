#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL.h>

#include <map>

#include "Define.h"

enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class Camera {
   public:
    static Camera CameraControl;

   private:
    int x;
    int y;

    int* targetX;
    int* targetY;

   public:
    int targetMode;

   public:
    Camera();

   public:
    void OnMove(std::map<int, bool>& keyStates);

   public:
    int getX();
    int getY();

   public:
    void setPos(int x, int y);
    void setTarget(int* x, int* y);
};

#endif