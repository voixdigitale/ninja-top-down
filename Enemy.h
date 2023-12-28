#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter {
    public:
        Enemy(Vector2 pos, Texture2D tex);
        virtual void tick(float deltaTime) override;
        void setTarget(Character* character) { target = character; };
        virtual Vector2 getScreenPos() override;
        void setPos(Vector2 newPos) { worldPos = newPos; }
    private:
        Character* target;
        Vector2 toTarget;
        float damagePerSec{10.f};
        float radius{25.f};
};