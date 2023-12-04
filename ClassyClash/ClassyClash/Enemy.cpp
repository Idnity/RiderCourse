#include "Enemy.h"

#include <raylib.h>
#include <raymath.h>

Enemy::Enemy(int win_width, int win_height)
{
    TCharacter = TIdle;
    TWidth = static_cast<float>(TCharacter.width) /static_cast<float>(max_frames);
    THeight = static_cast<float>(TCharacter.height);
    
    screen_pos = {
        static_cast<float>(win_width) / 2.f - (0.5f * TWidth * scale),
        static_cast<float>(win_height) / 2.f - (0.5f * THeight * scale)
    };
}

Vector2 Enemy::GetWorldPos()
{ return world_pos; }

Rectangle Enemy::GetCollisionRec()
{
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        TWidth * scale,
        THeight * scale
    };
}


void Enemy::tick(float deltaTime)
{
    world_pos_lastframe = world_pos;
    // Input direction
    float speed{200.f};
    Vector2 input_direction{};
    if (IsKeyDown(KEY_A))
        input_direction.x -= 1.f;
    if (IsKeyDown(KEY_D))
        input_direction.x += 1.f;
    if (IsKeyDown(KEY_W))
        input_direction.y -= 1.f;
    if (IsKeyDown(KEY_S))
        input_direction.y += 1.f;
    if (Vector2Length(input_direction) != 0.f)
    {
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(input_direction), speed * deltaTime));
        input_direction.x < 0.f ? facingDirection = -1.f : facingDirection = 1.f;
        TCharacter = TRun;
    }
    else
    {
        TCharacter = TIdle;
    }

    // Animation update
    running_time += deltaTime;
    if (running_time >= update_time)
    {
        frame++;
        running_time = 0.f;
        if (frame > max_frames) frame = 0;
    }
}

void Enemy::draw()
{
    DrawTexturePro(TCharacter,
    Rectangle{frame * TWidth, 0.f, facingDirection * TWidth, THeight},
    Rectangle{screen_pos.x, screen_pos.y, scale * TWidth, scale * THeight},
    {0.f,0.f},
    0.f,
    WHITE);
}

void Enemy::UndoMovement()
{
    world_pos = world_pos_lastframe;
}
