
#pragma once
#include <raylib.h>

class Player
{
public:
    Camera3D camera;
    Player();
    void Update();

    Vector3 GetForward() const;

private:

    float yaw;
    float pitch;
};