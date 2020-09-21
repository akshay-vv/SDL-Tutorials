#include "Camera.h"

Camera Camera::CameraControl;
Camera::Camera() {
    x = y = 0;
    targetX = targetY = NULL;
    targetMode = TARGET_MODE_NORMAL;
}

void Camera::OnMove(int MoveX, int MoveY) {
    x += MoveX;
    y += MoveY;
}

int Camera::getX() {
    if (targetX) {
        if (targetMode == TARGET_MODE_CENTER) {
            return *targetX - (WWIDTH / 2);
        }
        return *targetX;
    }
    return x;
}

int Camera::getY() {
    if (targetY) {
        if (targetMode == TARGET_MODE_CENTER) {
            return *targetY - (WHEIGHT / 2);
        }
        return *targetY;
    }
    return y;
}

void Camera::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Camera::setTarget(float* x, float* y) {
    targetX = x;
    targetY = y;
}