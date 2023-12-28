#include "raylib.h"
#include "raymath.h"

#include "BaseCharacter.h"

BaseCharacter::BaseCharacter() {
}

void BaseCharacter::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
    return Rectangle {
        getScreenPos().x,
        getScreenPos().y + height * scale * 3 / 4,
        width * scale,
        height * scale / 4
    };
}

void BaseCharacter::tick(float deltaTime) {
    if (velocity.x < 0 && abs(velocity.x) > abs(velocity.y))
    {
        faceDirection = West;
    }

    if (velocity.x > 0 && abs(velocity.x) > abs(velocity.y))
    {
        faceDirection = East;
    }
    if (velocity.y < 0 && abs(velocity.y) > abs(velocity.x))
    {
        faceDirection = North;
    }

    if (velocity.y > 0 && abs(velocity.y) > abs(velocity.x))
    {
        faceDirection = South;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        worldPosLastFrame = worldPos;
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        maxFrames = 3;
    }
    else
    {
        maxFrames = 0; // Idle
    }
    velocity = {};

    // Update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.0f;
            if (frame > maxFrames)
                frame = 0;
        }

        // Draw Character
        Rectangle source{faceDirection * width, frame * height, width, height};
        Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
        DrawTexturePro(texture, source, dest, Vector2Zero(), 0.0, WHITE);
}