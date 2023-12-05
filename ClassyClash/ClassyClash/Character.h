#pragma once

#include "BaseCharacter.h"
#include <raylib.h>

class Character : public BaseCharacter
{
public:
    Character(int win_width, int win_height);
    virtual Vector2 GetScreenPos() override;
    virtual void tick(float deltaTime) override;
    void draw() override;
    Rectangle GetWeaponCollisionRec() {return weaponCollisionRec;}
    float GetHealth() const {return health;}
    void TakeDamage(float damage);

private:
    int window_width{};
    int window_height{};
    Texture2D TWeapon{};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};
