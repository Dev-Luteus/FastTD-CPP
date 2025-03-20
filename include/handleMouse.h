#ifndef HANDLE_MOUSE_H
#define HANDLE_MOUSE_H

#include "grid.h"
#include "enemySpawner.h"
#include "wall.h"
#include "spire.h"

class HandleMouse
{
private:
    Grid& grid;
    EnemySpawner& enemySpawner;
    Wall& wall;
    Spire& spire;

    [[nodiscard]] bool IsValidPlacement(int gridX, int gridY) const;

    [[nodiscard]] int GetGridX(int screenX) const;
    [[nodiscard]] int GetGridY(int screenY) const;

public:
    HandleMouse(Grid& grid, EnemySpawner& enemySpawner, Wall& wall, Spire& spire);

    void UpdateMouse();
};

#endif //HANDLE_MOUSE_H