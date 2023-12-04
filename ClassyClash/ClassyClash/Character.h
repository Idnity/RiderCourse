#pragma once
#include <raylib.h>

class Character
{
public:
    Character();
    ~Character();
    Vector2 GetWorldPos();
    void SetScreenPos(int windowWidth, int windowHeight);
    void tick(float deltaTime);
    void draw();

    

    private:
    Texture2D TCharacter;
    Texture2D TIdle { LoadTexture("characters/knight_idle_spritesheet.png") };
    Texture2D TRun { LoadTexture("characters/knight_run_spritesheet.png") };
    Vector2 screen_pos{};
    Vector2 world_pos{};
    float TWidth{};
    float THeight{};

    float facingDirection{1.f};
    
    // animation
    float running_time{};
    float frame{};
    const int max_frames{6};
    const float update_time{1.f/12.f};
};