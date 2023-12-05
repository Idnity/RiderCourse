#pragma once
#include <raylib.h>

class BaseCharacter
{
public:
    BaseCharacter();
    float speed{200.f};
    virtual void tick(float deltaTime);
    virtual void draw();
    Vector2 GetWorldPos(){ return world_pos; };
    virtual Vector2 GetScreenPos() = 0;
    Rectangle GetCollisionRec();
    void UndoMovement();
    bool GetAlive() {return alive;}
    void SetAlive(bool isAlive) { alive = isAlive;}

protected:
    Texture2D texture{};
    Texture2D TIdle{};
    Texture2D TRun{};
    Vector2 world_pos{};
    Vector2 world_pos_lastframe{};
    Vector2 velocity{};
    float TWidth{};
    float THeight{};

    float facingDirection{1.f};
    float scale{4};
    
    // animation
    float running_time{};
    int frame{};
    int max_frames{6};
    float update_time{1.f/12.f};

private:
    bool alive{true};
};
