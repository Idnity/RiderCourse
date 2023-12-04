#pragma once
#include <raylib.h>

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 KnightPos);
    Rectangle GetCollisionRec(Vector2 knightPos);
    
private:
    Vector2 world_pos{};
    Texture2D texture{};
    float scale{4.f};
};
