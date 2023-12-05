#include "Enemy.h"
#include <raylib.h>
#include <raymath.h>

Enemy::Enemy(Vector2 pos, Texture2D Idle, Texture2D Run, Character* startTarget)
{
    texture = Idle;
    TIdle = Idle;
    TRun = Run;
    world_pos = pos;
    TWidth = static_cast<float>(texture.width) /  static_cast<float>(max_frames);
    THeight = static_cast<float>(texture.height);
    setTarget(startTarget);
}

void Enemy::tick(float deltaTime)
{
    if (!GetAlive()) return;
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    
    BaseCharacter::tick(deltaTime);
    
    if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
    {
        target->TakeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(world_pos, target->GetWorldPos());
}





