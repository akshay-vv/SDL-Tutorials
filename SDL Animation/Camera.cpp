#include "Camera.h"

Camera Camera::CameraControl;
Camera::Camera() {
    x = y = 0;
    targetX = targetY = NULL;
    targetMode = TARGET_MODE_NORMAL;
}

void Camera::OnMove(std::map<int, bool>& keyStates) {
    const int xOffset = 5;
    const int yOffset = 5;
    if (keyStates[SDLK_UP])
        y += yOffset;
    if (keyStates[SDLK_DOWN])
        y -= yOffset;
    if (keyStates[SDLK_LEFT])
        x += xOffset;
    if (keyStates[SDLK_RIGHT])
        x -= xOffset;
}

int Camera::getX() {
    if (targetX) {
        if (targetMode == TARGET_MODE_CENTER) {
            return *targetX - (WWIDTH / 2);
        }
    }
    return x;
}

int Camera::getY() {
    if (targetY) {
        if (targetMode == TARGET_MODE_CENTER) {
            return *targetY - (WHEIGHT / 2);
        }
    }
    return y;
}

void Camera::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Camera::setTarget(int* x, int* y) {
    targetX = x;
    targetY = y;
}