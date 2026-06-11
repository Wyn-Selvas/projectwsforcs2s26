/*#include "player.h"
#include <raymath.h>
#include <cmath>

Player::Player()
{
    camera.position =
    {0.0f,
     2.0f,
     25.0f
    };

    camera.target =
    {0.0f,
     2.0f,
     0.0f
    };

    camera.up =
    {0.0f,
     1.0f,
     0.0f
    };

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
    float moveSpeed = 12.0f * GetFrameTime();
    float mouseSensitivity = 0.00005f;

    Vector2 mouseDelta = GetMouseDelta();
    DrawText(
    TextFormat("dx: %.1f dy: %.1f", mouseDelta.x, mouseDelta.y),
    10, 30, 20, WHITE
);///////

    yaw -= mouseDelta.x * mouseSensitivity;
    pitch -= mouseDelta.y * mouseSensitivity;

    if(pitch > 1.4f)
        pitch = 1.4f;
    if(pitch < -1.4f)
        pitch = -1.4f;

    Vector3 forward =
    {
        sinf(yaw),
        0.0f,
        cosf(yaw)
    };

    forward = Vector3Normalize(forward);

    Vector3 right =
    {
        forward.z,
        0.0f,
        -forward.x
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
        camera.position.x += right.x * moveSpeed;
        camera.position.z += right.z * moveSpeed;
    }
    if(IsKeyDown(KEY_D))
    {
        camera.position.x -= right.x * moveSpeed;
        camera.position.z -= right.z * moveSpeed;
    }

    if(camera.position.x > 95.0f)
        camera.position.x = 95.0f;
    if(camera.position.x < -95.0f)
        camera.position.x = -95.0f;
    if(camera.position.z > 95.0f)
        camera.position.z = 95.0f;
    if(camera.position.z < -95.0f)
        camera.position.z = -95.0f;

    camera.position.y = 2.0f;
    camera.target =
    {
        camera.position.x + cosf(pitch) * sinf(yaw),
        camera.position.y + sinf(pitch),
        camera.position.z + cosf(pitch) * cosf(yaw)
    };
}*/

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
    const float moveSpeed = 12.0f * GetFrameTime();
    const float mouseSensitivity = 0.001f;

    Vector2 mouseDelta = GetMouseDelta();

    //
    
    //mouseDelta.x = Clamp(mouseDelta.x, -2.0f, 2.0f);
    //mouseDelta.y = Clamp(mouseDelta.y, -2.0f, 2.0f);
    DrawText(TextFormat("dx: %.1f", mouseDelta.x), 10, 30, 20, WHITE);
DrawText(TextFormat("dy: %.1f", mouseDelta.y), 10, 60, 20, WHITE);
    yaw   -= mouseDelta.x * mouseSensitivity;
    pitch -= mouseDelta.y * mouseSensitivity;

    // About +/- 85 degrees
    const float pitchLimit = 1.48f;

    if (pitch > pitchLimit)  pitch = pitchLimit;
    if (pitch < -pitchLimit) pitch = -pitchLimit;

    Vector3 lookForward = GetForward();

    // Movement only on XZ plane
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

    if (IsKeyDown(KEY_W))
        camera.position = Vector3Add(camera.position,
                                     Vector3Scale(moveForward, moveSpeed));
    if (IsKeyDown(KEY_S))
        camera.position = Vector3Subtract(camera.position,
                                          Vector3Scale(moveForward, moveSpeed));
    if (IsKeyDown(KEY_A))
        camera.position = Vector3Subtract(camera.position,
                                          Vector3Scale(right, moveSpeed));
    if (IsKeyDown(KEY_D))
        camera.position = Vector3Add(camera.position,
                                     Vector3Scale(right, moveSpeed));

    camera.position.x = Clamp(camera.position.x, -95.0f, 95.0f);
    camera.position.z = Clamp(camera.position.z, -95.0f, 95.0f);
    camera.position.y = 2.0f;
    camera.target = Vector3Add(camera.position, lookForward);
}

