#include <raylib.h>
#include "game.h"
int main()
{   InitWindow(
        
        1280,
        720,
        "Target Range"
    );
    SetTargetFPS(60);
    DisableCursor();
    Game game;
    game.Run();
    CloseWindow();

    return 0;
}