#include "game.h"

int main()
{
    Game game;

    game.initialize();
    game.run();
    game.shutdown();

    return 0;
}
