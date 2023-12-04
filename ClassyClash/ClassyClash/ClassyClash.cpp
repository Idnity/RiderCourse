#include "Character.h"
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
    Vector2 map_pos{0.f,0.f};

    Character knight;
    knight.SetScreenPos(window_settings.width, window_settings.height);
    
    // GAME LOOP
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // GAME LOGIC
        knight.tick(GetFrameTime());

        // DRAW
        DrawTextureEx(TWorldMap, Vector2Scale(knight.GetWorldPos(), -1.f), 0.f, 4.f, WHITE);
        knight.draw();

        EndDrawing();
    }

    // UNLOADING
    UnloadTexture(TWorldMap);

    CloseWindow();
    return 0;
}
