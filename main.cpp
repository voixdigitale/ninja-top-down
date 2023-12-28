
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>
#include <random>

using namespace std;

int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int windowWidth{384};
    const int windowHeight{384};
    const float scale{4.0};
    const int tileSetSize{16};
    int score{};

    InitWindow(windowWidth, windowHeight, "Top Down Example");

    Texture2D map = LoadTexture("map/worldmap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Texture2D tileset = LoadTexture("map/TilesetNature.png");
    

    Character ninja{windowWidth, windowHeight, LoadTexture("characters/green-ninja.png")};

    Enemy skeleton{Vector2{scale * tileSetSize * 6, scale * tileSetSize * 3}, LoadTexture("characters/skeleton.png")};
    Enemy flam{Vector2{scale * tileSetSize * 12, scale * tileSetSize * 11}, LoadTexture("characters/flam.png")};
    Enemy greendemon{Vector2{scale * tileSetSize * 20, scale * tileSetSize * 15}, LoadTexture("characters/greendemon.png")};
    Enemy spirit{Vector2{scale * tileSetSize * 18, scale * tileSetSize * 20}, LoadTexture("characters/spirit.png")};
    
    Enemy* enemies[4] {
        &skeleton,
        &flam,
        &greendemon,
        &spirit
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&ninja);
    }

    // Update Loop
    //--------------------------------------------------------------------------------------
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw Map
        mapPos = Vector2Scale(ninja.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.0, scale, WHITE);

        // Draw Props
        Prop props[10]{
            Prop {Vector2{scale * tileSetSize * 4, scale * tileSetSize * 3}, tileset, Rectangle{tileSetSize*4, tileSetSize*9, tileSetSize, tileSetSize}}, //Rock
            Prop {Vector2{scale * tileSetSize * 4, scale * tileSetSize * 7}, tileset, Rectangle{tileSetSize*13, tileSetSize*14, tileSetSize, tileSetSize*2}}, //Log1
            Prop {Vector2{scale * tileSetSize * 5, scale * tileSetSize * 7}, tileset, Rectangle{tileSetSize*13, tileSetSize*13, tileSetSize, tileSetSize}}, //Stump
            Prop {Vector2{scale * tileSetSize * 16, scale * tileSetSize * 15}, tileset, Rectangle{tileSetSize*13, tileSetSize*13, tileSetSize, tileSetSize}}, //Stump
            Prop {Vector2{scale * tileSetSize * 15, scale * tileSetSize * 16}, tileset, Rectangle{tileSetSize*13, tileSetSize*14, tileSetSize, tileSetSize*2}}, //Log1
            Prop {Vector2{scale * tileSetSize * 18, scale * tileSetSize * 3}, tileset, Rectangle{tileSetSize*12, tileSetSize*14, tileSetSize, tileSetSize*2}}, //Log2
            Prop {Vector2{scale * tileSetSize * 6, scale * tileSetSize * 12}, tileset, Rectangle{tileSetSize*2, 0.f, tileSetSize * 2, tileSetSize * 2}}, //Tree
            Prop {Vector2{scale * tileSetSize * 7, scale * tileSetSize * 13}, tileset, Rectangle{tileSetSize*2, 0.f, tileSetSize * 2, tileSetSize * 2}}, //Tree
            Prop {Vector2{scale * tileSetSize * 5, scale * tileSetSize * 16}, tileset, Rectangle{tileSetSize*2, 0.f, tileSetSize * 2, tileSetSize * 2}}, //Tree
            Prop {Vector2{scale * tileSetSize * 17, scale * tileSetSize * 8}, tileset, Rectangle{tileSetSize*2, 0.f, tileSetSize * 2, tileSetSize * 2}}, //Tree
        };

        for (auto prop : props) {
            prop.Render(ninja.getWorldPos());
        }

        if (!ninja.getAlive()) {
            DrawText("Game Over", 15.f, 15.f, 25, RED);
            EndDrawing();
            continue;
        } else {
            string ninjaHealth = "Health: ";
            ninjaHealth.append(to_string(ninja.getHealth()), 0, 5);
            DrawText(ninjaHealth.c_str(), 15.f, 15.f, 25, RED);
        }

        string scoreText = "Score: ";
        scoreText.append(to_string(score));
        DrawText(scoreText.c_str(), 230.f, 15.f, 25, RED);

        ninja.tick(GetFrameTime());
        if (ninja.getWorldPos().x < 0.f ||
            ninja.getWorldPos().y < 0.f ||
            ninja.getWorldPos().x + windowWidth > map.width * scale ||
            ninja.getWorldPos().y + windowHeight > map.height * scale) {
                ninja.undoMovement();
        }

        for (auto prop : props) {
            if(CheckCollisionRecs(prop.getCollisionRec(ninja.getWorldPos()), ninja.getCollisionRec())) {
                ninja.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            // Ressucitate fallen enemies
            if (!enemy->getAlive()) {
                Vector2 newPos {
                    static_cast<float>(getRandomNumber(0, map.width * scale)), 
                    static_cast<float>(getRandomNumber(0, map.height * scale))
                };
                
                enemy->setPos(newPos);
                enemy->setAlive(true);
            }

            enemy->tick(GetFrameTime());
        }


        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            for (auto enemy : enemies) {
                if (CheckCollisionRecs(enemy->getCollisionRec(), ninja.getWeaponCollisionRec())) {
                    enemy->setAlive(false);
                    score++;
                }
            }
        }

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(map);

    CloseWindow();
}
