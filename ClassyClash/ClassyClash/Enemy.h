#pragma once
#include <raylib.h>

#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D Idle, Texture2D Run, Character* startTarget);
    void tick(float deltaTime) override;
    void setTarget(Character* character) {target = character;}
    virtual Vector2 GetScreenPos() override;

private:
    Character* target;
    float damagePerSec{10.f};
    float radius {25.f};
};
