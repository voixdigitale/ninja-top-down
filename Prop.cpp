#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex, Rectangle rec) : 
    worldPos(pos),
    texture(tex),
    sourceRec(rec)
{  
};

void Prop::Render(Vector2 playerPos) {
    DrawTexturePro(texture, sourceRec, getDestRec(playerPos), Vector2Zero(), 0.0, WHITE);
};

Rectangle Prop::getCollisionRec(Vector2 playerPos) {
    return getDestRec(playerPos);
}

Rectangle Prop::getDestRec(Vector2 playerPos) {
    screenPos = Vector2Subtract(worldPos, playerPos);
    return Rectangle {screenPos.x, screenPos.y, scale * sourceRec.width, scale * sourceRec.height};
}