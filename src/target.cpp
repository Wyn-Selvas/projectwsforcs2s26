#include "target.h"
#include <raymath.h>
#include <cmath>

Target::Target()
{   radius = 1.0f;
    active = true;
    position = {0,0,0};
    velocity = {0,0,0};

    Respawn(false);
}

void Target::Respawn(bool moving)
{   active = true;
    position =
    {   (float)GetRandomValue(-90, 90),
        (float)GetRandomValue(2, 8),
        (float)GetRandomValue(-90, 90)
    };

    velocity = {0,0,0};

    if(moving)
    {
        float speed =
            (float)GetRandomValue(3, 10);
        float angle =
            DEG2RAD *
            (float)GetRandomValue(0,359);

        velocity =
        {
            cosf(angle) * speed,
            0.0f,
            sinf(angle) * speed
        };
    }
}

void Target::Update(float dt, bool moving)
{
    if(!active)
        return;
    if(!moving)
        return;

    position.x += velocity.x * dt;
    position.z += velocity.z * dt;

    if(position.x > 100.0f)
        position.x = -100.0f;
    if(position.x < -100.0f)
        position.x = 100.0f;
    if(position.z > 100.0f)
        position.z = -100.0f;
    if(position.z < -100.0f)
        position.z = 100.0f;
}

bool Target::CheckHit(Vector3 arrowPosition)
{
    if(!active)
        return false;

    float dx =
        arrowPosition.x - position.x;
    float dy =
        arrowPosition.y - position.y;
    float dz =
        arrowPosition.z - position.z;
    float distance =
        sqrtf(
            dx * dx +
            dy * dy +
            dz * dz
        );

    if(distance <= radius)
    {
        active = false;
        return true;
    }

    return false;
}

void Target::Draw()
{
    if(!active)
        return;

    Vector3 front =
    {
        position.x,
        position.y,
        position.z
    };
    Vector3 back =
    {
        position.x,
        position.y,
        position.z + 0.15f
    };

   DrawCylinderEx(
        front,
        back,
        1.0f,
        1.0f,
        32,
        WHITE
    );
    DrawCylinderEx(
        front,
        back,
        0.8f,
        0.8f,
        32,
        BLACK
    );
    DrawCylinderEx(
        front,
        back,
        0.6f,
        0.6f,
        32,
        BLUE
    );
    DrawCylinderEx(
        front,
        back,
        0.4f,
        0.4f,
        32,
        RED
    );
    DrawCylinderEx(
        front,
        back,
        0.2f,
        0.2f,
        32,
        YELLOW
    );
}