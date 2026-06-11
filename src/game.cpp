#include "game.h"
#include <raylib.h>
#include <raymath.h>
#include <algorithm>

Game::Game()
{
    screen = MENU;
    mode = STILL;

    score = 0;
    shotsFired = 0;
    hits = 0;

    selectedTargetCount = 10;
    targetsRemaining = 0;

    raceTimer = 0.0f;

    bowCharge = 0.0f;
    charging = false;

    movingTargets = false;
}

float Game::GetAccuracy() const
{
    if(shotsFired == 0)
        return 0.0f;
    return
        (100.0f * hits) /
        (float)shotsFired;
}

bool Game::HasFlyingArrow() const
{
    for(const auto& arrow : arrows)
    {   if(arrow.IsFlying())
            return true;
    }

    return false;
}

void Game::ResetGame()
{   score = 0;
    shotsFired = 0;
    hits = 0;

    raceTimer = 0.0f;

    bowCharge = 0.0f;
    charging = false;

    targetsRemaining = selectedTargetCount;

    arrows.clear();
    targets.clear();
}
void Game::SpawnSingleTarget(bool moving)
{   targets.clear();
    Target target;
    target.Respawn(moving);
    targets.push_back(target);
}
void Game::SpawnMultiTargets(int count)
{   targets.clear();

    for(int i = 0; i < count; i++)
    {   Target target;
        target.Respawn(true);
        targets.push_back(target);
    }
}
void Game::UpdateArrows(float dt)
{
    for(auto& arrow : arrows)
    {
        arrow.Update(dt);
    }

    arrows.erase(
        std::remove_if(
            arrows.begin(),
            arrows.end(),
            [](const Arrow& arrow)
            {
                return arrow.state == DEAD;
            }
        ),
        arrows.end()
    );
}

void Game::CheckArrowCollisions()
{
    for(auto& arrow : arrows)
    {
        if(!arrow.IsFlying())
            continue;

        for(auto& target : targets)
        {
            if(!target.active)
                continue;

            if(target.CheckHit(arrow.position))
            {
                hits++;
                score++;

                arrow.state = DEAD;

                if(mode == STILL)
                {
                    target.Respawn(false);
                }
                else if(mode == MOVING_SINGLE)
                {
                    target.Respawn(true);
                }
                else if(mode == TIMED_RACE)
                {
                    targetsRemaining--;
                    if(targetsRemaining > 0)
                    {   target.Respawn(false);
                    }
                }
                break;
            }
        }
    }
    if(mode == MULTI_TARGET)
    {
        int remaining = 0;
        for(const auto& target : targets)
        {
            if(target.active)
            {
                remaining++;
            }
        }
        targetsRemaining = remaining;
    }
}
void Game::UpdateGameplay(float dt)
{
    player.Update();
    if(mode == TIMED_RACE)
    {    raceTimer += dt;
    }

    for(auto& target : targets)
    {    target.Update(dt, movingTargets);
    }

    UpdateArrows(dt);
    CheckArrowCollisions();

    bool allowShoot = true;

    if(mode == STILL ||
       mode == MOVING_SINGLE ||
       mode == TIMED_RACE)
    {   allowShoot = !HasFlyingArrow();
    }
    if(IsKeyPressed(KEY_SPACE) && allowShoot)
    {   charging = true;
        bowCharge = 0.0f;
    }
    if(charging && IsKeyDown(KEY_SPACE))
    {
        bowCharge += dt;
        if(bowCharge > 3.0f)
        {
            bowCharge = 3.0f;
        }
    }
    if(charging && IsKeyReleased(KEY_SPACE))
    {
        charging = false;
        Arrow arrow;
        Vector3 direction =
            player.GetForward();

        float power =
            20.0f +
            (bowCharge * 20.0f);
        Vector3 start =
        {   player.camera.position.x,
            player.camera.position.y,
            player.camera.position.z
        };

        arrow.Shoot(
            start,
            direction,
            power
        );

        arrows.push_back(arrow);

        shotsFired++;
    }

    if(mode == TIMED_RACE)
    {
        if(targetsRemaining <= 0)
        {
            screen = RESULTS;
        }
    }

    if(mode == MULTI_TARGET)
    {
        if(targetsRemaining <= 0)
        {
            screen = RESULTS;
        }
    }

    if(IsKeyPressed(KEY_M))
    {
        screen = MENU;
    }
}
void Game::DrawWorld()
{
    BeginMode3D(player.camera);
    DrawPlane(
        {0,0,0},
        {200,200},
        DARKGREEN
    );
    DrawGrid(20,10);

    for(auto& target : targets)
    {
        target.Draw();
    }

    for(auto& arrow : arrows)
    {
        arrow.Draw();
    }

    EndMode3D();
}
void Game::DrawHUD()
{
    DrawText(
        TextFormat(
            "Score: %d",
            score
        ),
        20,
        20,
        30,
        BLACK
    );
    DrawText(
        TextFormat(
            "Accuracy: %.1f%%",
            GetAccuracy()
        ),
        20,
        60,
        30,
        BLACK
    );

    if(mode == TIMED_RACE)
    {
        DrawText(
            TextFormat(
                "Targets Left: %d",
                targetsRemaining
            ),
            20,
            100,
            30,
            RED
        );

        DrawText(
            TextFormat(
                "Time: %.1f",
                raceTimer
            ),
            20,
            140,
            30,
            RED
        );
    }

    if(mode == MULTI_TARGET)
    {
        DrawText(
            TextFormat(
                "Targets Left: %d",
                targetsRemaining
            ),
            20,
            100,
            30,
            RED
        );

        DrawText(
            TextFormat(
                "Target Count: %d",
                selectedTargetCount
            ),
            20,
            140,
            30,
            RED
        );
    }

    if(charging)
    {
        DrawRectangle(
            20,
            190,
            300,
            25,
            LIGHTGRAY
        );

        DrawRectangle(
            20,
            190,
            (int)(100 * bowCharge),
            25,
            RED
        );

        DrawText(
            "Bow Power",
            20,
            220,
            20,
            BLACK
        );
    }

    int cx =
        GetScreenWidth() / 2;

    int cy =
        GetScreenHeight() / 2;

    DrawLine(
        cx - 10,
        cy,
        cx + 10,
        cy,
        BLACK
    );

    DrawLine(
        cx,
        cy - 10,
        cx,
        cy + 10,
        BLACK
    );
}
void Game::DrawMenu()
{
    ClearBackground(BLACK);
    DrawText(
        "ARCHERY RANGE",
        400,
        100,
        50,
        WHITE
    );
    DrawText(
        "1 - Still Target",
        420,
        220,
        30,
        WHITE
    );
    DrawText(
        "2 - Moving Target",
        420,
        270,
        30,
        WHITE
    );
    DrawText(
        "3 - Timed Race",
        420,
        320,
        30,
        WHITE
    );
    DrawText(
        "4 - Multi Target",
        420,
        370,
        30,
        WHITE
    );
    DrawText(
        TextFormat(
            "Target Count: %d",
            selectedTargetCount
        ),
        420,
        450,
        30,
        YELLOW
    );
    DrawText(
        "UP / DOWN = Change Count",
        420,
        490,
        25,
        WHITE
    );
    if(IsKeyPressed(KEY_UP))
    {
        selectedTargetCount++;
        if(selectedTargetCount > 100)
        {
            selectedTargetCount = 100;
        }
    }
    if(IsKeyPressed(KEY_DOWN))
    {
        selectedTargetCount--;
        if(selectedTargetCount < 1)
        {
            selectedTargetCount = 1;
        }
    }
    if(IsKeyPressed(KEY_ONE))
    {
        ResetGame();
        mode = STILL;
        movingTargets = false;
        SpawnSingleTarget(false);
        screen = PLAYING;
    }
    if(IsKeyPressed(KEY_TWO))
    {
        ResetGame();
        mode = MOVING_SINGLE;
        movingTargets = true;
        SpawnSingleTarget(true);
        screen = PLAYING;
    }

    if(IsKeyPressed(KEY_THREE))
    {
        ResetGame();
        mode = TIMED_RACE;
        movingTargets = false;
        SpawnSingleTarget(false);
        screen = PLAYING;
    }

    if(IsKeyPressed(KEY_FOUR))
    {
        ResetGame();
        mode = MULTI_TARGET;
        movingTargets = true;
        SpawnMultiTargets(
            selectedTargetCount
        );
        targetsRemaining =
            selectedTargetCount;
        screen = PLAYING;
    }
}

void Game::DrawResults()
{
    ClearBackground(DARKBLUE);
    DrawText(
        "RESULTS",
        500,
        120,
        50,
        WHITE
    );
    DrawText(
        TextFormat(
            "Score: %d",
            score
        ),
        450,
        250,
        35,
        WHITE
    );
    DrawText(
        TextFormat(
            "Accuracy: %.1f%%",
            GetAccuracy()
        ),
        450,
        310,
        35,
        WHITE
    );
    if(mode == TIMED_RACE)
    {
        DrawText(
            TextFormat(
                "Time: %.2f",
                raceTimer
            ),
            450,
            370,
            35,
            YELLOW
        );
    }
    DrawText(
        "Press ENTER For Menu",
        380,
        500,
        30,
        WHITE
    );

    if(IsKeyPressed(KEY_ENTER))
    {
        screen = MENU;
    }
}
void Game::Run()
{
    while(!WindowShouldClose())
    {
        float dt =
            GetFrameTime();
        BeginDrawing();
        if(screen == MENU)
        {   DrawMenu();
        }
        else if(screen == PLAYING)
        {   ClearBackground(SKYBLUE);
            UpdateGameplay(dt);
            DrawWorld();
            DrawHUD();
        }

        else if(screen == RESULTS)
        {   DrawResults();
        }
        EndDrawing();
    }
}