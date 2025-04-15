#include "game.h"
#include "profileScope.h"

int main()
{
    PROFILE_INIT("fastTD_performance_log.txt");
    {
        Game game;

        game.Initialize();
        game.Run();
        game.Shutdown();
    }

    Profiler::PrintSummary();
    return 0;
}
