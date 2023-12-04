#pragma once

class Enemy
{
public:
    Character(int win_width, int win_height);
    ~Character();
    Vector2 GetWorldPos();
    Rectangle GetCollisionRec();
    void SetScreenPos(int windowWidth, int windowHeight);
    void tick(float deltaTime);
    void draw();
    void UndoMovement();

    

private:
    Texture2D TCharacter;
    Texture2D TIdle { LoadTexture("characters/knight_idle_spritesheet.png") };
    Texture2D TRun { LoadTexture("characters/knight_run_spritesheet.png") };
    Vector2 screen_pos{};
    Vector2 world_pos{};
    Vector2 world_pos_lastframe{};
    float TWidth{};
    float THeight{};

    float facingDirection{1.f};
    float scale{4};
    
    // animation
    float running_time{};
    float frame{};
    const int max_frames{6};
    const float update_time{1.f/12.f};
};
