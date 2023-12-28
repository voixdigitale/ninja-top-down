#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    virtual void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture;
    float height;
    float width;
    float scale{4.0};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    enum FaceDirection
    {
        South,
        North,
        West,
        East
    };
    FaceDirection faceDirection{South};
    float speed{3.0};
    float runningTime{};
    int frame{};
    int maxFrames{3};
    const float updateTime{1.f / 12.f};
    Vector2 velocity;

private:
    bool alive{true};
};

#endif