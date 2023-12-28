#include "raylib.h"

class Prop {
    public:
        Prop(Vector2 pos, Texture2D tex, Rectangle rec);
        void Render(Vector2 playerPos);
        Rectangle getCollisionRec(Vector2 playerPos);
    private:
        Vector2 worldPos{};
        Vector2 screenPos{};
        Texture2D texture{};
        Rectangle sourceRec;
        float scale{4.f};
        Rectangle getDestRec(Vector2 playerPos);
};