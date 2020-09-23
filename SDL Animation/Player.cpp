#include "Player.h"

CPlayer::CPlayer() {
}

bool CPlayer::OnLoad(SDL_Renderer* renderer, std::string& file, int width, int height, int maxFrames) {
    if (Entity::OnLoad(renderer, file, width, height, maxFrames) == false) {
        return false;
    }

    return true;
}

void CPlayer::OnLoop() {
    Entity::OnLoop();
}

void CPlayer::OnRender() {
    Entity::OnRender();
}

void CPlayer::OnCleanup() {
    Entity::OnCleanup();
}

void CPlayer::OnAnimate() {
    if (speedX != 0) {
        animControl.maxFrames = 8;
    } else {
        animControl.maxFrames = 0;
    }

    Entity::OnAnimate();
}

bool CPlayer::OnCollision(Entity* Entity) {
    jump();
    return true;
}