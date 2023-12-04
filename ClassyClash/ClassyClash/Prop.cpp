#include "Prop.h"

#include <raymath.h>

Prop::Prop(Vector2 pos, Texture2D tex):
    world_pos(pos),
    texture(tex)
{
}

void Prop::Render(Vector2 KnightPos)
{
    Vector2 screen_pos{Vector2Subtract(world_pos, KnightPos)};
    DrawTextureEx(texture, screen_pos, 0.f, scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 knightPos)
{
    Vector2 screen_pos{Vector2Subtract(world_pos, knightPos)};
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        static_cast<float>(texture.width) * scale,
        static_cast<float>(texture.height) * scale
    };
}
