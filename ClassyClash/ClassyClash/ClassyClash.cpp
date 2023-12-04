#include "Character.h"
#include "Prop.h"
#include "raylib.h"
#include "raymath.h"


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
    Prop props[2]
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
        knight.draw();
        for (auto prop : props)
        {
            prop.Render(knight.GetWorldPos());
        }
        
        EndDrawing();
    }

    // UNLOADING
    UnloadTexture(TWorldMap);

    CloseWindow();
    return 0;
}
