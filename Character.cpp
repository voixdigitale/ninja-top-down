#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int winWidth, int winHeight, Texture2D tex) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    texture = tex;
    width = texture.width / 4.0f;
    height = texture.height / 7.0f;
}

Vector2 Character::getScreenPos() {
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;

    if (IsKeyDown(KEY_A))
    {
        velocity.x -= 1.0;
    }

    if (IsKeyDown(KEY_D))
    {
        velocity.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        velocity.y -= 1.0;
    }

    if (IsKeyDown(KEY_S))
    {
        velocity.y += 1.0;
    }
    
    // Draw sword
    int swordFace;
    Vector2 origin{};
    Vector2 offset{};
    float weaponRot;

    switch (faceDirection)
    {
        case North:
            swordFace = -1;
            origin = {static_cast<float>(weapon.width), static_cast<float>(weapon.height)};
            offset = {45.f, 55.f};
            weaponCollisionRec = {
                getScreenPos().x,
                getScreenPos().y - offset.y,
                static_cast<float>(weapon.width),
                static_cast<float>(weapon.height) + 20.f
            };
            weaponRot = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 45.f : 80.f;
            break;
        case West:
            swordFace = -1;
            origin = {static_cast<float>(weapon.width), static_cast<float>(weapon.height)};
            offset = {25.f, 55.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x - static_cast<float>(weapon.width),
                getScreenPos().y,
                static_cast<float>(weapon.width) + 20.f,
                static_cast<float>(weapon.height)
            };
            weaponRot = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
            break;
        case East:
            swordFace = 1;
            BaseCharacter::tick(deltaTime);
            origin = {0.f, static_cast<float>(weapon.height)};
            offset = {45.f, 55.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x,
                getScreenPos().y,
                static_cast<float>(weapon.width) + 20.f,
                static_cast<float>(weapon.height)
            };
            weaponRot = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;

            break;
        case South:
            swordFace = -1;
            BaseCharacter::tick(deltaTime);
            origin = {static_cast<float>(weapon.width), static_cast<float>(weapon.height)};
            offset = {25.f, 45.f};
            weaponCollisionRec = {
                getScreenPos().x ,
                getScreenPos().y + offset.y,
                static_cast<float>(weapon.width),
                static_cast<float>(weapon.height) + 20.f
            };
            weaponRot = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -135.f : -100.f;
            break;

        default:
            break;
    }

    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width * swordFace), static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, static_cast<float>(weapon.width), static_cast<float>(weapon.height)};
    DrawTexturePro(weapon, source, dest, origin, weaponRot, WHITE);

    if (faceDirection == North || faceDirection == West) {
        BaseCharacter::tick(deltaTime);
    }

}

void Character::takeDamage(float damage) {
    health -= damage;
    if (health <= 0.f) {
        setAlive(false);
    }
}