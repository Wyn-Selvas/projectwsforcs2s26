#include "game.h"

Game::Game()
{
    screen = MENU;
    mode = STILL;

    score = 0;
    timer = 300.0f;
    selectedTargetCount = 10;
    ResetTargets(selectedTargetCount);
}

void Game::ResetTargets(int count)
{
    targets.clear();

    for(int i = 0; i < count; i++)
    {
        Target t;

        t.position =
        {
            (float)GetRandomValue(-15,15),
            (float)GetRandomValue(2,8),
            -30.0f - (float)GetRandomValue(0,20)
        };

        targets.push_back(t);
    }
}

void Game::Run()
{
    while(!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_ESCAPE))
        {
            break;
        }

        BeginDrawing();

        if(screen == MENU)
        {
            ClearBackground(BLACK);

            DrawText("Targets",420,120,60,WHITE);

            DrawText("Press 1 - STILL TARGETS",430,250,30,WHITE);
            DrawText("Press 2 - TIMED MODE",430,300,30,WHITE);
            DrawText("Press 3 - MOVING TARGET",430,350,30,WHITE);
            DrawText("Press 4 - MOVING MULTI TARGET",430,400,30,WHITE);

            DrawText("ESC - QUIT",430,500,30,RED);
            if(IsKeyPressed(KEY_UP))
    {
                selectedTargetCount++;
                if(selectedTargetCount > 100)
                selectedTargetCount = 100;
}

if(IsKeyPressed(KEY_DOWN))
{
    selectedTargetCount--;

    if(selectedTargetCount < 1)
        selectedTargetCount = 1;
}
            if(IsKeyPressed(KEY_ONE))
            {
                mode = STILL;
                score = 0;
                ResetTargets(selectedTargetCount);
                screen = PLAYING;
            }

            if(IsKeyPressed(KEY_TWO))
            {
                mode = TIMED;
                score = 0;
                timer = 300.0f;
                ResetTargets(selectedTargetCount);
                screen = PLAYING;
            }

            if(IsKeyPressed(KEY_THREE))
            {
                mode = MOVING_SINGLE;
                score = 0;
                ResetTargets(selectedTargetCount);
                screen = PLAYING;
            }

            if(IsKeyPressed(KEY_FOUR))
            {
                mode = MOVING_MULTI;
                score = 0;
                ResetTargets(selectedTargetCount);
                screen = PLAYING;
            }

            EndDrawing();
            continue;
        }

        float dt = GetFrameTime();

        player.Update();

        bool moving =
        (
            mode == MOVING_SINGLE ||
            mode == MOVING_MULTI
        );

        for(auto& t : targets)
        {
            t.Update(dt,moving);
        }

        if(mode == TIMED)
        {
            timer -= dt;

            if(timer <= 0)
            {
                timer = 0;
                screen = MENU;
            }
        }

        if(IsKeyPressed(KEY_M))
        {
            screen = MENU;
        }

        if(IsKeyPressed(KEY_SPACE))

        {
            Vector2 center =
            {
                GetScreenWidth()/2.0f,
                GetScreenHeight()/2.0f
            };

            Ray ray =
            GetScreenToWorldRay(center,player.camera);

            for(auto& t : targets)
{
    if(t.active && t.CheckHit(ray))
    {
        score += 10;

        break;
    }
}
        }

        ClearBackground(SKYBLUE);

        BeginMode3D(player.camera);

        DrawPlane({0,0,0},{100,100},DARKGREEN);//grasss

        for(auto& t : targets)
        {
            t.Draw();
        }

        EndMode3D();

        DrawText(
            TextFormat("Score: %i",score),
            20,
            20,
            30,
            BLACK
        );

        if(mode == TIMED)
        {
            DrawText(
                TextFormat("Time: %.0f",timer),
                20,
                60,
                30,
                RED
            );
        }

        DrawText(
            "M = Menu",
            20,
            100,
            20,
            BLACK
        );

        DrawText(
            "ESC = Quit",
            20,
            130,
            20,
            BLACK
        );
        DrawText(
    TextFormat("Target Count: %d", selectedTargetCount),
    430,
    450,
    30,
    YELLOW
);
        DrawText(
    "UP/DOWN = Change Target Count",
    430,
    490,
    25,
    WHITE
);

        int cx = GetScreenWidth()/2;
        int cy = GetScreenHeight()/2;

        DrawLine(cx-10,cy,cx+10,cy,BLACK);
        DrawLine(cx,cy-10,cx,cy+10,BLACK);
       // DrawFPS(20,170); // Uncomment to show FPS
        EndDrawing();
    }
}