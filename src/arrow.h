#pragma once
#include <raylib.h>

enum ArrowState
{
    FLYING,
    STUCK_GROUND,
    DEAD
};

class Arrow
{
public:

    Vector3 position;
    Vector3 velocity;

    ArrowState state;

    Arrow();

    void Shoot(
        Vector3 start,
        Vector3 direction,
        float power
    );

    void Update(float dt);
    void Draw();

    bool IsFlying() const;
    bool IsAlive() const;
};