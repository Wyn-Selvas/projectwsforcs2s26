#pragma once
#include <raylib.h>

class Player
{
public:
    Camera3D camera;

    Player();
    void Update();

private:
    float yaw;
    float pitch;
};