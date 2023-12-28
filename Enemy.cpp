#include "raylib.h"
#include "raymath.h"
#include "Enemy.h"
#include "Character.h"

Enemy::Enemy(Vector2 pos, Texture2D tex)
{
    worldPos = pos;
    texture = tex;
    width = texture.width / 4.0f;
    height = texture.height / 7.0f;
    speed = 1.f;
}

void Enemy::tick(float deltaTime) {
    if (!getAlive()) return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius) velocity = {};

    toTarget = Vector2Normalize(Vector2Subtract(target->getScreenPos(), getScreenPos()));

    worldPos = Vector2Add(worldPos, Vector2Scale(toTarget, speed));

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())) {
        target->takeDamage(damagePerSec * deltaTime);
    }

    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos() {
    return Vector2Subtract(worldPos, target->getWorldPos());
}