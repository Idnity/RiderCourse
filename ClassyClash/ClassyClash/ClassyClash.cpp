#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include "raylib.h"
#include "raymath.h"
#include <string>

struct window_properties
{
    int width{384};
    int height{384};
    const char* title{"ClassyClash"};
    int target_fps{240};
};
window_properties window_settings;


int main()
{
    // WINDOW SETUP
    InitWindow(window_settings.width, window_settings.height, window_settings.title);
    SetTargetFPS(window_settings.target_fps);
    
    // MAP
    Texture2D TWorldMap = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 map_pos{};
    const float map_scale{4.f};


    // INSTANCES
    Character knight{window_settings.width, window_settings.height};

    Enemy goblin{{200.f,500.f},LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"), &knight};
    Enemy goblin2{{-1200.f,500.f},LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"), &knight};
    Enemy goblin3{{600.f,1000.f},LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"), &knight};
    Enemy goblin4{{200.f,-1500.f},LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"), &knight};
    Enemy slime{{1000.f,500.f},LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png"), &knight};
    Enemy slime2{{-1000.f,-500.f},LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png"), &knight};
    Enemy slime3{{700.f,1000.f},LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png"), &knight};
    
    Enemy* enemies[]
    {
        &goblin,
        &goblin2,
        &goblin3,
        &goblin4,
        &slime,
        &slime2,
        &slime3
    };
    
    Prop props[]
    {
        Prop{{600.f,300.f},LoadTexture("nature_tileset/Rock.png")},
        Prop{{400.f,500.f},LoadTexture("nature_tileset/Log.png")}
    };
    
    // GAME LOOP
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // GAME LOGIC
        knight.tick(GetFrameTime());
        
        
        
        // CHECK MAP BOUNDS
        if (knight.GetWorldPos().x < 0.f ||
            knight.GetWorldPos().y < 0.f ||
            knight.GetWorldPos().x + static_cast<float>(window_settings.width) > static_cast<float>(TWorldMap.width) * map_scale ||
            knight.GetWorldPos().y + static_cast<float>(window_settings.height) > static_cast<float>(TWorldMap.height) * map_scale)
        {
            knight.UndoMovement();
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(knight.GetWorldPos()), knight.GetCollisionRec()))
            {
                knight.UndoMovement();
            }
        }

        // DRAW
        map_pos = Vector2Scale(knight.GetWorldPos(), -1.f);
        DrawTextureEx(TWorldMap, map_pos, 0.f, map_scale, WHITE);
        
        for (auto prop : props)
        {
            prop.Render(knight.GetWorldPos());
        }

        if (knight.GetAlive())
        {
            std::string knightsHealth{"Health: "};
            knightsHealth.append(std::to_string(knight.GetHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        else
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        
        knight.draw();
        for (auto enemy : enemies)
        {
            enemy->draw();
        }
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(knight.GetWeaponCollisionRec(), enemy->GetCollisionRec()))
                {
                    enemy->SetAlive(false);
                }
            }
        }
        
        
        EndDrawing();
    }

    // UNLOADING
    UnloadTexture(TWorldMap);

    CloseWindow();
    return 0;
}
