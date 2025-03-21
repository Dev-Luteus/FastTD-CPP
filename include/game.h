#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "obstacles.h"
#include "spire.h"
#include "enemySpawner.h"
#include "gameCamera.h"
#include "handleMouse.h"
#include "wall.h"

class Game
{
// this private: accessor is unnecessary, but I will include it in every file
private:
    static constexpr int SCREEN_WIDTH { 1920 };
    static constexpr int SCREEN_HEIGHT { 1080 };

    Grid grid;
    Spire spire;
    Obstacles obstacles;
    EnemySpawner enemySpawner;
    Wall wall;
    HandleMouse* mouseHandler { nullptr };
    GameCamera camera;

    void Draw();
    void Update(float deltaTime);
    void DrawUI();
public:
    Game();

    void Initialize();
    void Run();
    void Shutdown();
};

#endif //GAME_H
