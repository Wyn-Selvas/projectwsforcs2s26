#include "player.h"
#include <cmath>

Player::Player()
{
    camera.position = {0.0f, 2.0f, 25.0f};
    camera.target = {0.0f, 2.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    yaw = 3.14159f;
    pitch = 0.0f;
}

void Player::Update()
{
    float moveSpeed = 0.2f;
    float turnSpeed = 0.002f;

    if(IsKeyDown(KEY_LEFT))
        yaw += turnSpeed;

    if(IsKeyDown(KEY_RIGHT))
        yaw -= turnSpeed;

    Vector3 forward =
    {
        sinf(yaw),
        0,
        cosf(yaw)
    };

    if(IsKeyDown(KEY_W))
    {
        camera.position.x += forward.x * moveSpeed;
        camera.position.z += forward.z * moveSpeed;
    }

    if(IsKeyDown(KEY_S))
    {
        camera.position.x -= forward.x * moveSpeed;
        camera.position.z -= forward.z * moveSpeed;
    }

    if(IsKeyDown(KEY_A))
    {
        camera.position.x += forward.z * moveSpeed;
        camera.position.z -= forward.x * moveSpeed;
    }

    if(IsKeyDown(KEY_D))
    {
        camera.position.x -= forward.z * moveSpeed;
        camera.position.z += forward.x * moveSpeed;
    }
    if(IsKeyDown(KEY_LEFT))
    yaw += turnSpeed;

if(IsKeyDown(KEY_RIGHT))
    yaw -= turnSpeed;

if(IsKeyDown(KEY_UP))
    pitch += turnSpeed;

if(IsKeyDown(KEY_DOWN))
    pitch -= turnSpeed;
    if(pitch > 1.2f)
    pitch = 1.2f;

if(pitch < -1.2f)
    pitch = -1.2f;

    float dx = camera.position.x;
    float dz = camera.position.z;

    float dist = sqrt(dx*dx + dz*dz);

    if(dist < 15.0f)
    {
        float scale = 15.0f / dist;
        camera.position.x *= scale;
        camera.position.z *= scale;
    }

    if(dist > 40.0f)
    {
        float scale = 40.0f / dist;
        camera.position.x *= scale;
        camera.position.z *= scale;
    }

   camera.target =
{
    camera.position.x + cosf(pitch) * sinf(yaw),
    camera.position.y + sinf(pitch),
    camera.position.z + cosf(pitch) * cosf(yaw)
};

}