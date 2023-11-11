#include "raylib.h"

    // window dimentions
    const int window_width = 800;
    const int window_height = 500;
 
    // rectangle
    int width = 50;
    int height = 80;
    Texture2D Tscarfy;
    Rectangle scarfyRec;
    Vector2 scarfyPos;
    
    int pos_y = window_height - height;
    int velocity = 0;
    int jump_velocity = -20;

    int gravity = 1;

bool is_in_air()
{
    return pos_y + height < window_height;
}

int main()
{
    InitWindow(window_width, window_height, "DapperDasher");

    Tscarfy = LoadTexture("textures/scarfy.png");
    scarfyRec.width = Tscarfy.width/6;
    scarfyRec.height = Tscarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    
    // game loop
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // air check
        if (is_in_air())
        {
            // in air
            velocity += gravity;
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
        pos_y += velocity;

        
        // draw
        DrawRectangle(window_width/2, pos_y, width, height, BLUE);
        

        EndDrawing();
    }
    CloseWindow();
}

