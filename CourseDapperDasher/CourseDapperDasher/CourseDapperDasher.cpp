#include "raylib.h"
#include<iostream> 
using namespace std;

    // window dimensions
    const int window_width = 500;
    const int window_height = 350;

    float velocity = 0;
    int jump_velocity = -600;
    float neb_vel = -200;
    int gravity = 1'000;

struct anim_data
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float update_time;
    float running_time;
};

bool is_on_ground(anim_data anim, int windowHeight)
{
    return anim.pos.y >= window_height - anim.rec.height;
}

void update_anim_data(anim_data& anim, int max_frame)
{
    anim.running_time += GetFrameTime();
    if (anim.running_time >= anim.update_time)
    {
        anim.rec.x = float(anim.frame) * anim.rec.width;
        anim.frame = anim.frame + 1 % max_frame;
        anim.running_time = 0;
    }
}

int main()
{
    InitWindow(window_width, window_height, "DapperDasher");

    // load textures
    Texture2D Tscarfy = LoadTexture("textures/scarfy.png");
    Texture2D TNebula = LoadTexture("textures/nebula.png");
    Texture2D TBackground = LoadTexture("textures/far-buildings.png");
    Texture2D TBuildings = LoadTexture("textures/back-buildings.png");
    Texture2D TForeground = LoadTexture("textures/foreground.png");
    
    // scarfy anim data
    anim_data scarfyAnim
    {
        {0, 0, float(Tscarfy.width)/6,float(Tscarfy.height)},
        {window_width/2.0f - float(Tscarfy.width)/6/2, window_height - float(Tscarfy.height)},
        0,
        1.0f/12.0f,
        0
    };

    // setup nebulae
    anim_data nebulae[5]{};
    for (int i = 0; i < int(size(nebulae)); ++i)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = float(TNebula.width)/8.0f;
        nebulae[i].rec.height = float(TNebula.height)/8.0f;
        nebulae[i].pos.y = window_height - float(TNebula.height)/8.0f;
        nebulae[i].frame = 0;
        nebulae[i].running_time = 0;
        nebulae[i].update_time = 1.0f/16.0f;
        nebulae[i].pos.x = float(window_width) + 300.0f * float(i);
    }

    float finish_line = nebulae[size(nebulae) - 1].pos.x;
    bool collision = false;

    // background parralax
    float bgX{};
    float bgX2{};
    float bgX3{};
    
    
    // game loop
    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        // parralax
        bgX -= 20 * GetFrameTime();
        if (bgX <= - float(TBackground.width)*2)
        {
            bgX = 0.0;
        }
        bgX2 -= 40 * GetFrameTime();
        if (bgX2 <= - float(TBuildings.width)*2)
        {
            bgX2 = 0.0;
        }
        bgX3 -= 80 * GetFrameTime();
        if (bgX3 <= - float(TForeground.width)*2)
        {
            bgX3 = 0.0;
        }
        
        DrawTextureEx(TBackground, {bgX, 0}, 0, 2, WHITE);
        DrawTextureEx(TBackground, {bgX + float(TBackground.width)*2, 0}, 0, 2, WHITE);
        
        DrawTextureEx(TBuildings, {bgX2, 0}, 0, 2, WHITE);
        DrawTextureEx(TBuildings, {bgX2 + float(TBuildings.width)*2, 0}, 0, 2, WHITE);
        
        DrawTextureEx(TForeground, {bgX3, 0}, 0, 2, WHITE);
        DrawTextureEx(TForeground, {bgX3 + float(TForeground.width)*2, 0}, 0, 2, WHITE);
        
        // air check
        if (is_on_ground(scarfyAnim, window_height))
        {
            // on ground
            velocity = 0.0;
        }
        else
        {
            // in air
            velocity += float(gravity) * GetFrameTime();
        }
        
        // input
        if ((IsKeyDown(KEY_SPACE)) && is_on_ground(scarfyAnim, window_height))
        {
            velocity += float(jump_velocity);
        }

        
        // update positions
        scarfyAnim.pos.y += velocity * GetFrameTime();
        finish_line += neb_vel * GetFrameTime();
        for (auto& nebula : nebulae)
        {
            nebula.pos.x += neb_vel * GetFrameTime();
        }

        for (auto nebula : nebulae)
        {
            float pad = 50;
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - pad*2,
                nebula.rec.height - pad*2
            };
            Rectangle scarfyRec{
                scarfyAnim.pos.x,
                scarfyAnim.pos.y,
                scarfyAnim.rec.width,
                scarfyAnim.rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        
        // player animation
        if (is_on_ground(scarfyAnim, window_height))
        {
            update_anim_data(scarfyAnim, 5);
        }
        
        // nebula animation
        for (auto& nebula : nebulae)
        {
            update_anim_data(nebula, 7);
        }

        if (collision)
        {
            // loose the game
            DrawText("Game Over!", window_width/4, window_height/2, 40, RED);
        }
        else
        {
            // draw
            DrawTextureRec(Tscarfy, scarfyAnim.rec, scarfyAnim.pos, WHITE);
            for (auto& nebula : nebulae)
            {
                DrawTextureRec(TNebula, nebula.rec, nebula.pos, WHITE);
            }
            if (scarfyAnim.pos.x > finish_line)
            {
                DrawText("You Win!", window_width/4, window_height/2, 40, WHITE);
            }
        }
        
        EndDrawing();
    }
    
    UnloadTexture(Tscarfy);
    UnloadTexture(TNebula);
    UnloadTexture(TBackground);
    UnloadTexture(TBuildings);
    UnloadTexture(TForeground);
    CloseWindow();

 
}

