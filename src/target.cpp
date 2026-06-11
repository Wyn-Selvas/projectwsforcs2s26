#include "target.h"

Target::Target()
{
    position =
    {
        (float)GetRandomValue(-20,20),
        (float)GetRandomValue(2,8),
        (float)GetRandomValue(-20,20)
    };

    radius = 3.0f;
    active = true;

    velocity =
    {
        (float)GetRandomValue(-5,5), 0,
        (float)GetRandomValue(-5,5)
    };
}

void Target::Update(float dt,bool moving)
{
    if(!moving) return;
    position.x += velocity.x * dt;
    position.z += velocity.z * dt;

    if(position.x > 25 || position.x < -25)
        velocity.x *= -1;

    if(position.z > 25 || position.z < -25)
        velocity.z *= -1;
}

bool Target::CheckHit(Ray ray)
{
    RayCollision hit =
        GetRayCollisionSphere(ray,position,radius);

    if(hit.hit)
    {
        active = false;
        return true;
    }

    return false;
}


void Target::Draw()
{
    if(!active) return;

    Vector3 front = position;
    Vector3 back =
    {
        position.x,
        position.y,
        position.z + 0.1f
    };

    DrawCylinderEx(front, back, 1.0f, 1.0f, 32, WHITE);
    DrawCylinderEx(front, back, 0.8f, 0.8f, 32, BLACK);
    DrawCylinderEx(front, back, 0.6f, 0.6f, 32, BLUE);
    DrawCylinderEx(front, back, 0.4f, 0.4f, 32, RED);
    DrawCylinderEx(front, back, 0.2f, 0.2f, 32, YELLOW);
}