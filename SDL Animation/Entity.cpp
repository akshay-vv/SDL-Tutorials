#include "Entity.h"

#include <string>

#include "Texture.h"
std::vector<Entity*> Entity::entityList;

Entity::Entity() {
    textureEntity = NULL;
    x = y = 0.0f;
    width = height = 0;
    animState = 0;
}

Entity::~Entity() {
}

bool Entity::OnLoad(SDL_Renderer* renderer, std::string file, int width, int height, int maxFrames) {
    textureEntity = new Texture(renderer, file, 255, 0, 255);
    this->width = width;
    this->height = height;

    animControl.maxFrames = maxFrames;
    return true;
}

void Entity::OnLoop() {
    animControl.OnAnimate();
}

void Entity::OnRender() {
    textureEntity->OnDraw(x, y, animState * width, animControl.getCurrentFrame() * height, width, height);
}

void Entity::OnCleanup() {
    delete textureEntity;
    textureEntity = NULL;
}