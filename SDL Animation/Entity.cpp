#include "Entity.h"

#include <string>

#include "Camera.h"
#include "FPS.h"
#include "Texture.h"

std::vector<Entity*> Entity::entityList;

Entity::Entity() {
    textureEntity = NULL;

    x = y = 0.0f;
    width = height = 0;

    moveLeft = false;
    moveRight = false;

    canJump = false;

    type = ENTITY_TYPE_GENERIC;
    dead = false;
    flags = ENTITY_FLAG_GRAVITY;

    speedX = 0;  // Current Speed
    speedY = 0;

    accelX = 0;  // Rate of Speed
    accelY = 0;

    maxSpeedX = 10;  // Speed Cap
    maxSpeedY = 10;

    currentFrameCol = 0;  // Which Frame to pick from the animation image
    currentFrameRow = 0;

    col_X = 0;  // Collision offsets
    col_Y = 0;
    col_Height = 0;
    col_Width = 0;
}

Entity::~Entity() {
}

bool Entity::OnLoad(SDL_Renderer* renderer, std::string& file, int width, int height, int maxFrames) {
    textureEntity = new Texture(renderer, file);
    this->width = width;
    this->height = height;

    animControl.maxFrames = maxFrames;
    return true;
}

void Entity::OnLoop() {
    //We're not Moving
    if (moveLeft == false && moveRight == false) {
        stopMove();
    }

    if (moveLeft) {
        accelX = -0.5;
    } else

        if (moveRight) {
        accelX = 0.5;
    }

    if (flags & ENTITY_FLAG_GRAVITY) {
        accelY = 0.75f;
    }

    speedX += accelX * FPS::FPSControl.getSpeedFactor();
    speedY += accelY * FPS::FPSControl.getSpeedFactor();

    if (speedX > maxSpeedX) speedX = maxSpeedX;
    if (speedX < -maxSpeedX) speedX = -maxSpeedX;
    if (speedY > maxSpeedY) speedY = maxSpeedY;
    if (speedY < -maxSpeedY) speedY = -maxSpeedY;

    OnAnimate();
    OnMove(speedX, speedY);
}

void Entity::OnRender() {
    textureEntity->OnDraw(
        x - Camera::CameraControl.getX(), y - Camera::CameraControl.getY(),
        currentFrameCol * width, (currentFrameRow + animControl.getCurrentFrame()) * height,
        width, height);
}

void Entity::OnAnimate() {
    if (moveLeft) {
        currentFrameCol = 0;
    } else

        if (moveRight) {
        currentFrameCol = 1;
    }

    animControl.OnAnimate();
}

bool Entity::jump() {
    if (canJump == false) return false;

    speedY = -maxSpeedY;

    return true;
}

bool Entity::OnCollision(Entity* Entity) {
    return false;
}

void Entity::OnMove(float moveX, float moveY) {
    if (moveX == 0 && moveY == 0) return;

    canJump = false;

    double newX = 0;
    double newY = 0;

    moveX *= FPS::FPSControl.getSpeedFactor();
    moveY *= FPS::FPSControl.getSpeedFactor();

    if (moveX != 0) {
        if (moveX >= 0)
            newX = FPS::FPSControl.getSpeedFactor();
        else
            newX = -FPS::FPSControl.getSpeedFactor();
    }

    if (moveY != 0) {
        if (moveY >= 0)
            newY = FPS::FPSControl.getSpeedFactor();
        else
            newY = -FPS::FPSControl.getSpeedFactor();
    }

    while (true) {
        if (flags & ENTITY_FLAG_GHOST) {
            posValid((int)(x + newX), (int)(y + newY));  //We don't care about collisions, but we need to send events to other entities

            x += newX;
            y += newY;
        } else {
            if (posValid((int)(x + newX), (int)(y))) {
                x += newX;
            } else {
                speedX = 0;
            }

            if (posValid((int)(x), (int)(y + newY))) {
                y += newY;
            } else {
                if (moveY > 0) {
                    canJump = true;
                }
                speedY = 0;
            }
        }

        moveX += -newX;
        moveY += -newY;

        if (newX > 0 && moveX <= 0) newX = 0;
        if (newX < 0 && moveX >= 0) newX = 0;

        if (newY > 0 && moveY <= 0) newY = 0;
        if (newY < 0 && moveY >= 0) newY = 0;

        if (moveX == 0) newX = 0;
        if (moveY == 0) newY = 0;

        if (moveX == 0 && moveY == 0) break;
        if (newX == 0 && newY == 0) break;
    }
}

void Entity::stopMove() {
    if (speedX > 0) {
        accelX = -1;
    }

    if (speedX < 0) {
        accelX = 1;
    }

    if (speedX < 2.0f && speedX > -2.0f) {
        accelX = 0;
        speedX = 0;
    }
}

bool Entity::collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    int tX = (int)x + col_X;
    int tY = (int)y + col_Y;

    left1 = tX;
    left2 = oX;

    right1 = left1 + width - 1 - col_Width;
    right2 = oX + oW - 1;

    top1 = tY;
    top2 = oY;

    bottom1 = top1 + height - 1 - col_Height;
    bottom2 = oY + oH - 1;

    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;

    if (right1 < left2) return false;
    if (left1 > right2) return false;

    return true;
}

bool Entity::posValid(int NewX, int NewY) {
    bool result = true;

    int StartX = (NewX + col_X) / TILE_WIDTH;
    int StartY = (NewY + col_Y) / TILE_HEIGHT;

    int EndX = ((NewX + col_X) + width - col_Width - 1) / TILE_WIDTH;
    int EndY = ((NewY + col_Y) + height - col_Height - 1) / TILE_HEIGHT;

    for (int iY = StartY; iY <= EndY; iY++) {
        for (int iX = StartX; iX <= EndX; iX++) {
            Tile* tile = Area::AreaControl.GetTile(iX * TILE_WIDTH, iY * TILE_HEIGHT);

            if (posValidTile(tile) == false) {
                result = false;
            }
        }
    }

    if (flags & ENTITY_FLAG_MAPONLY) {
    } else {
        for (int i = 0; i < entityList.size(); i++) {
            if (posValidEntity(entityList[i], NewX, NewY) == false) {
                result = false;
            }
        }
    }

    return result;
}

bool Entity::posValidTile(Tile* Tile) {
    if (Tile == NULL) {
        return true;
    }

    if (Tile->type == TILE_TYPE_BLOCK) {
        return false;
    }

    return true;
}

bool Entity::posValidEntity(Entity* Entity, int NewX, int NewY) {
    if (this != Entity && Entity != NULL && Entity->dead == false &&
        Entity->flags ^ ENTITY_FLAG_MAPONLY &&
        Entity->collides(NewX + col_X, NewY + col_Y, width - col_Width - 1, height - col_Height - 1) == true) {
        EntityCol EntityCol;

        EntityCol.entityA = this;
        EntityCol.entityB = Entity;

        EntityCol::EntityColList.push_back(EntityCol);

        return false;
    }

    return true;
}

void Entity::OnCleanup() {
    delete textureEntity;
    textureEntity = NULL;
}