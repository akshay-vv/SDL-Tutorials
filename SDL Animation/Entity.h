#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <string>
#include <vector>

#include "Animation.h"
#include "Area.h"

enum {
    ENTITY_TYPE_GENERIC = 0,

    ENTITY_TYPE_PLAYER
};

enum {
    ENTITY_FLAG_NONE = 0,

    ENTITY_FLAG_GRAVITY = 0x00000001,
    ENTITY_FLAG_GHOST = 0x00000002,
    ENTITY_FLAG_MAPONLY = 0x00000004
};

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

    bool moveLeft;
    bool moveRight;

   public:
    int type;
    bool dead;
    int flags;

   protected:
    float speedX;
    float speedY;

    float accelX;
    float accelY;

   public:
    float maxSpeedX;
    float maxSpeedY;

   protected:
    int currentFrameCol;
    int currentFrameRow;

   protected:
    int col_X;
    int col_Y;
    int col_Width;
    int col_Height;

   public:
    Entity();
    virtual ~Entity();

   public:
    virtual bool OnLoad(SDL_Renderer* renderer, std::string& file, int width, int height, int maxFrames);
    virtual void OnLoop();
    virtual void OnRender();
    virtual void OnCleanup();
    virtual void OnAnimate();
    virtual bool OnCollision(Entity* entity);

   public:
    void OnMove(float moveX, float moveY);
    void stopMove();

   protected:
    bool canJump;

   public:
    bool jump();

   public:
    bool collides(int oX, int oY, int oW, int oH);

   private:
    bool posValid(int newX, int newY);
    bool posValidTile(Tile* tile);
    bool posValidEntity(Entity* entity, int newX, int newY);
};

class EntityCol {
   public:
    static std::vector<EntityCol> EntityColList;

   public:
    Entity* entityA;
    Entity* entityB;

   public:
    EntityCol();
};
#endif