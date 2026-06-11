#include <raylib.h>
#include "game.h"

int main()
{
    InitWindow(1280,720,"Targets");
    SetTargetFPS(60);

    Game game;
    game.Run();
    CloseWindow();

    return 0;
}