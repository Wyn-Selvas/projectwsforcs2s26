
#pragma once
#include <raylib.h>

class Target
{
public:

    Vector3 position;
    Vector3 velocity;

    float radius;
    bool active;

    Target();

    void Respawn(bool moving);
    void Update(float dt, bool moving);
    bool CheckHit(Vector3 arrowPosition);
    void Draw();
};