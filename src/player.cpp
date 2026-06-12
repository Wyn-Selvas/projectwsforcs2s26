#include "player.h"
#include <raymath.h>
#include <cmath>

Player::Player()
{
    camera.position = { 0.0f, 2.0f, 25.0f };
    camera.target   = { 0.0f, 2.0f, 24.0f };
    camera.up       = { 0.0f, 1.0f, 0.0f };

    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    yaw = PI;
    pitch = 0.0f;
}

Vector3 Player::GetForward() const
{
    Vector3 forward =
    {
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    };

    return Vector3Normalize(forward);
}

void Player::Update()
{
    const float moveSpeed = 9.5f * GetFrameTime(); // Adjust movement speed based on frame time
    const float turnSpeed = 0.6f * GetFrameTime();// adjust view rotation speed

    // Arrow keys control camera rotation
    if (IsKeyDown(KEY_LEFT))
        yaw += turnSpeed;

    if (IsKeyDown(KEY_RIGHT))
        yaw -= turnSpeed;

    if (IsKeyDown(KEY_UP))
        pitch += turnSpeed;

    if (IsKeyDown(KEY_DOWN))
        pitch -= turnSpeed;

    // Limit vertical look angle
    const float pitchLimit = 1.48f;

    if (pitch > pitchLimit)  pitch = pitchLimit;
    if (pitch < -pitchLimit) pitch = -pitchLimit;

    Vector3 lookForward = GetForward();

    // Movement stays on the ground plane
    Vector3 moveForward =
    {
        lookForward.x,
        0.0f,
        lookForward.z
    };

    moveForward = Vector3Normalize(moveForward);

    Vector3 right =
    {
        -moveForward.z,
         0.0f,
         moveForward.x
    };

    // WASD movement
    if (IsKeyDown(KEY_W))
        camera.position = Vector3Add(
            camera.position,
            Vector3Scale(moveForward, moveSpeed)
        );
    if (IsKeyDown(KEY_S))
        camera.position = Vector3Subtract(
            camera.position,
            Vector3Scale(moveForward, moveSpeed)
        );
    if (IsKeyDown(KEY_A))
        camera.position = Vector3Subtract(
            camera.position,
            Vector3Scale(right, moveSpeed)
        );
    if (IsKeyDown(KEY_D))
        camera.position = Vector3Add(
            camera.position,
            Vector3Scale(right, moveSpeed)
        );

    // player bounds
    camera.position.x = Clamp(camera.position.x, -95.0f, 95.0f);
    camera.position.z = Clamp(camera.position.z, -95.0f, 95.0f);
    camera.position.y = 2.0f;

    // camera target
    camera.target = Vector3Add(camera.position, lookForward);

}