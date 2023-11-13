#include "raylib.h"

    // window dimentions
    const int window_width = 800;
    const int window_height = 500;
 
    Texture2D Tscarfy;
    Rectangle scarfyRec;
    Vector2 scarfyPos;
    
    int velocity = 0;
    int jump_velocity = -600;

    int gravity = 1'000;

bool is_in_air()
{
    return scarfyPos.y + scarfyRec.height < window_height;
}

int main()
{
    InitWindow(window_width, window_height, "DapperDasher");

    // nebula
    Texture2D TNebula = LoadTexture("12_nebula_spritesheet.png");
    
    // scarfy
    Tscarfy = LoadTexture("textures/scarfy.png");
    scarfyRec.width = Tscarfy.width/6;
    scarfyRec.height = Tscarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    
    int frame = 0;
    const float updateTime = 1.0/12.0;
    float RunningTime = 0;   

    scarfyPos.x = window_width/2 - scarfyRec.width/2;
    scarfyPos.y = window_height - scarfyRec.height;

    
    // game loop
    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // air check
        if (is_in_air())
        {
            // in air
            velocity += gravity * GetFrameTime();
        }
        else
        {
            // on ground
            velocity = 0;
        }
        
        // input
        if ((IsKeyDown(KEY_SPACE)) && !is_in_air())
        {
            velocity += jump_velocity;
        }

        
        // update position
        scarfyPos.y += velocity * GetFrameTime();

        
        // draw
        RunningTime += GetFrameTime();
        if (RunningTime >= updateTime)
        {
            scarfyRec.x = frame * scarfyRec.width;
            frame = frame + 1 % 5;
            RunningTime = 0;
        }
        
        DrawTextureRec(Tscarfy, scarfyRec, scarfyPos, WHITE);
        

        EndDrawing();
    }
    
    UnloadTexture(Tscarfy);
    UnloadTexture(TNebula);
    CloseWindow();
}

