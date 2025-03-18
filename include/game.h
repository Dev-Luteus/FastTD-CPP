#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "obstacles.h"
#include "spire.h"
#include "enemySpawner.h"

class Game
{
// this private: is unnecessary, but I will include it in every file
private:
    static constexpr int SCREEN_WIDTH { 1920 };
    static constexpr int SCREEN_HEIGHT { 1080 };

    Grid grid;
    Spire spire;
    Obstacles obstacles;
    EnemySpawner enemy_spawner;

    void Draw();
    void Update(float deltaTime);
public:
    Game() = default; // Default Constructor no args ( if no args = use default )

    void Initialize();
    void Run();
    void Shutdown();
};

#endif //GAME_H
