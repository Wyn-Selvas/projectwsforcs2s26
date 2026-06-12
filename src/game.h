#pragma once
#include <vector>
#include "player.h"
#include "target.h"
#include "arrow.h"

enum GameMode
{
    STILL,
    MOVING_SINGLE,
    TIMED_RACE,
    MULTI_TARGET
};

enum ScreenState
{
    MENU,
    PLAYING,
    RESULTS
};

class Game
{
public:
    Game();
    void Run();

private:

    Player player;

    std::vector<Target> targets;
    std::vector<Arrow> arrows;

    GameMode mode;
    ScreenState screen;

    int score;
    int shotsFired;
    int hits;
    int selectedTargetCount;
    int targetsRemaining;
    float raceTimer;
    float Charge;
    bool charging;
    bool movingTargets;
    float GetAccuracy() const;
    bool HasFlyingArrow() const;

    void ResetGame();
    void SpawnSingleTarget(bool moving);
    void SpawnMultiTargets(int count);
    void UpdateGameplay(float dt);
    void UpdateArrows(float dt);
    void CheckArrowCollisions();
    void DrawWorld();
    void DrawHUD();
    void DrawMenu();
    void DrawResults();
};