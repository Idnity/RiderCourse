#include "Character.h"
#include <raymath.h>


Character::Character(int win_width, int win_height) :
    window_width(win_width), window_height(win_height)
{
    speed = 300.f;
    TIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    TRun = LoadTexture("characters/knight_run_spritesheet.png");
    TWeapon = LoadTexture("characters/weapon_sword.png");
    
    texture = TIdle;
    TWidth = static_cast<float>(texture.width) /static_cast<float>(max_frames);
    THeight = static_cast<float>(texture.height);
};


Vector2 Character::GetScreenPos()
{
    return Vector2{
    static_cast<float>(window_width) / 2.f - (0.5f * TWidth * scale),
    static_cast<float>(window_height) / 2.f - (0.5f * THeight * scale)
    };
}

void Character::tick(float deltaTime)
{
    if (!GetAlive()) return;
    
    // Input direction
    velocity = {};
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.f;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.f;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.f;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.f;
    
    BaseCharacter::tick(deltaTime);
}

void Character::draw()
{
    if (!GetAlive()) return;
    
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (facingDirection > 0.f)
    {
        origin = {0.f, TWeapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            GetScreenPos().x + offset.x,
            GetScreenPos().y + offset.y - TWeapon.height * scale,
            TWeapon.width * scale,
            TWeapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = {TWeapon.width * scale, TWeapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            GetScreenPos().x + offset.x - TWeapon.width * scale,
            GetScreenPos().y + offset.y - TWeapon.height * scale,
            TWeapon.width * scale,
            TWeapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }
        
    // draw sword
    Rectangle source{0.f,0.f, static_cast<float>(TWeapon.width) * facingDirection,static_cast<float>(TWeapon.height)};
    Rectangle dest{GetScreenPos().x + offset.x,GetScreenPos().y + offset.y, static_cast<float>(TWeapon.width) * scale, static_cast<float>(TWeapon.height) * scale};
    DrawTexturePro(TWeapon, source, dest, origin, rotation, WHITE);
    
    BaseCharacter::draw();
}

void Character::TakeDamage(float damage)
{
    health -= damage;
    if (health < 0.f)
    {
        SetAlive(false);
    }
}
