#include "game.h"

int main()
{
    Game game;

    game.Initialize();
    game.Run();
    game.Shutdown();

    return 0;
}
