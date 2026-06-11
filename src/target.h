#pragma once
#include <raylib.h>

class Target
{
public:
    Vector3 position;
    float radius;
    bool active;

    Vector3 velocity;
    Target();

    void Update(float dt,bool moving);
    bool CheckHit(Ray ray);
    void Draw();
};
