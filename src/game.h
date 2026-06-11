#pragma once

#include <vector>
#include "player.h"
#include "target.h"

enum GameMode
{
    STILL,
    TIMED,
    MOVING_SINGLE,
    MOVING_MULTI
};

enum ScreenState
{
    MENU,
    PLAYING
};

class Game
{
public:
    Game();
    void Run();

private:
    Player player;
    std::vector<Target> targets;
    GameMode mode;
    ScreenState screen;

    int score;
    float timer;
    int selectedTargetCount;

    void ResetTargets(int count);
};
