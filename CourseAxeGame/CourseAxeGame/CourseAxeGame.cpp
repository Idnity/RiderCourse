#include "raylib.h"

// window dimensions, init window
int window_width = 800;
int window_height = 450;

// circle dimensions
int circle_x = window_width/2;
int circle_y = window_height/2;
int circle_radius = 25;
// circle edges
int l_circle_x(){return circle_x - circle_radius;}
int r_circle_x(){return circle_x + circle_radius;}
int u_circle_y(){return circle_y - circle_radius;}
int b_circle_y(){return circle_y + circle_radius;}


// axe properties
int axe_x = 50;
int axe_y = 0;
int axe_length = 50;
int axe_direction = 10;
// axe edges
int l_axe_x(){return axe_x;}
int r_axe_x(){return axe_x + axe_length;}
int u_axe_y(){return axe_y;}
int b_axe_y(){return axe_y + axe_length;}
    
// game mode variables
bool collision_with_axe()
{
    return          (b_axe_y() >= u_circle_y()) &&
                    (u_axe_y() <= b_circle_y()) &&
                    (r_axe_x() >= l_circle_x()) &&
                    (l_axe_x() <= r_circle_x());
}

int main()
{
    InitWindow(window_width,window_height,"AxeGame");
    SetTargetFPS(60);
    
    // draw
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (collision_with_axe())
        {
            DrawText("Game Over!", window_width/2, window_height/2, 20, RED);
        }
        else
        {
            // Game logic
            DrawCircle(circle_x, circle_y, circle_radius, GREEN);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // move axe
            axe_y += axe_direction;
            if (axe_y > window_height || axe_y < 0)
            {
                axe_direction = -axe_direction;
            }
            
            // input
            if (IsKeyDown(KEY_D) && circle_x < window_width)
            {
                circle_x += 10;
            }
            if (IsKeyDown(KEY_A) && circle_x > 0)
            {
                circle_x -= 10;
            }
        }

        // game logic ends
        EndDrawing();
    }
}   
