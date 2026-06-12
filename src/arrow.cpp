#include "arrow.h"
#include <raymath.h>

Arrow::Arrow()
{   position = {0.0f, 0.0f, 0.0f};
    velocity = {0.0f, 0.0f, 0.0f};
    state = DEAD;
}

void Arrow::Shoot(
    Vector3 start,
    Vector3 direction,
    float power
)
{
    position = start;

    velocity =
    {   direction.x * power,
        direction.y * power,
        direction.z * power
    };

    state = FLYING;
}

void Arrow::Update(float dt)
{
    if(state != FLYING)
        return;

    const float gravity = 9.8f;

    velocity.y -= gravity * dt;
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;

    if(position.y <= 0.1f)
    {   position.y = 0.1f;
        velocity = {0.0f, 0.0f, 0.0f};
        state = STUCK_GROUND;
    }

    if(fabs(position.x) > 250.0f ||
       fabs(position.z) > 250.0f)
    {
        state = DEAD;
    }
}

void Arrow::Draw()
{
    if(state == DEAD)
        return;
    if(state == STUCK_GROUND)
    {
        Vector3 tip =
        {   position.x,
            position.y + 1.0f,
            position.z
        };

        DrawCylinderEx(
            position,
            tip,
            0.03f,
            0.02f,
            8,
            BROWN
        );

        DrawRectangle(
            tip.x - 0.05f,
            tip.y - 0.05f,
            0.1f,
            0.1f,
            DARKBROWN
        );

        return;
    }

    Vector3 dir = Vector3Normalize(velocity);

    Vector3 tail =
    {   position.x - dir.x * 1.0f,
        position.y - dir.y * 1.0f,
        position.z - dir.z * 1.0f
    };

    DrawCylinderEx(
        tail,
        position,
        0.03f,
        0.02f,
        8,
        BROWN
    );

    DrawSphere(
        position,
        0.05f,
        RED
    );

    Vector3 feather1 =
    {  tail.x + 0.08f,
       tail.y,
       tail.z
    };

    Vector3 feather2 =
    {   tail.x - 0.08f,
        tail.y,
        tail.z
    };

    DrawLine3D(
        tail,
        feather1,
        RED
    );

    DrawLine3D(
        tail,
        feather2,
        RED
    );
}

bool Arrow::IsFlying() const
{
    return state == FLYING;
}
bool Arrow::IsAlive() const
{
    return state != DEAD;
}