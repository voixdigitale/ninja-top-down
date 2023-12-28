#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter 
{
    public:
        Character(int winWidth, int winHeight, Texture2D tex);
        Vector2 getWorldPos() { return worldPos; }
        virtual void tick(float deltaTime) override;
        virtual Vector2 getScreenPos() override;
        Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
        float getHealth() const { return health; }
        void takeDamage(float damage);
    private:
        int windowWidth{};
        int windowHeight{};
        Texture2D weapon {LoadTexture("characters/weapon_katana.png")};
        Rectangle weaponCollisionRec{};
        float health{100.f};
};

#endif