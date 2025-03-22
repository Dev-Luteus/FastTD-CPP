#ifndef HANDLE_MOUSE_H
#define HANDLE_MOUSE_H

#include "grid.h"
#include "enemySpawner.h"
#include "gameCamera.h"
#include "wall.h"
#include "spire.h"

class HandleMouse
{
private:
    Grid& grid;
    EnemySpawner& enemySpawner;
    Wall& wall;
    Spire& spire;
    GameCamera& camera;
    Player& player;
    RoundManager& roundManager;

    const int SCREEN_WIDTH;
    const int UI_WIDTH;

    [[nodiscard]] bool IsValidPlacement(int gridX, int gridY) const;
    [[nodiscard]] bool IsInsideUI(Vector2 mousePos) const;

    [[nodiscard]] int GetGridX(int screenX) const;
    [[nodiscard]] int GetGridY(int screenY) const;

public:
    HandleMouse(Grid& grid, EnemySpawner& enemySpawner,
        Wall& wall, Spire& spire, GameCamera& camera, Player& player,
        RoundManager& roundManager, int screenWidth, int uiWidth);

    void UpdateMouse();
};

#endif //HANDLE_MOUSE_H