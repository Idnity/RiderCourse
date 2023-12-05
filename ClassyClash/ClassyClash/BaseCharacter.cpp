#include "BaseCharacter.h"

#include <raymath.h>

BaseCharacter::BaseCharacter()
{
    
}

void BaseCharacter::tick(float deltaTime)
{
    world_pos_lastframe = world_pos;

    if (Vector2Length(velocity) != 0.f)
    {
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(velocity), speed * deltaTime));
        velocity.x < 0.f ? facingDirection = -1.f : facingDirection = 1.f;
        texture = TRun;
    }
    else
    {
        texture = TIdle;
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

void BaseCharacter::draw()
{
    if (!alive) {return;}
    
    DrawTexturePro(texture,
    Rectangle{frame * TWidth, 0.f, facingDirection * TWidth, THeight},
    Rectangle{GetScreenPos().x, GetScreenPos().y, scale * TWidth, scale * THeight},
    {0.f,0.f},
    0.f,
    WHITE);
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        GetScreenPos().x,
        GetScreenPos().y,
        TWidth * scale,
        THeight * scale
    };
}

void BaseCharacter::UndoMovement()
{
    world_pos = world_pos_lastframe;
}