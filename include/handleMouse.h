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

    [[nodiscard]] bool IsValidPlacement(int gridX, int gridY) const;

    [[nodiscard]] int GetGridX(int screenX) const;
    [[nodiscard]] int GetGridY(int screenY) const;

public:
    HandleMouse(Grid& grid, EnemySpawner& enemySpawner, Wall& wall, Spire& spire, GameCamera& camera);

    void UpdateMouse();
};

#endif //HANDLE_MOUSE_H