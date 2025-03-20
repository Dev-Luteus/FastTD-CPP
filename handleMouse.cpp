#include "handleMouse.h"
#include <raylib.h>

HandleMouse::HandleMouse(Grid& grid, EnemySpawner& enemySpawner, Wall& wall, Spire& spire)
    : grid(grid), enemySpawner(enemySpawner), wall(wall), spire(spire)
{
}

int HandleMouse::GetGridX(int screenX) const
{
    return screenX / Cell::CELL_SIZE;
}

int HandleMouse::GetGridY(int screenY) const
{
    return screenY / Cell::CELL_SIZE;
}

bool HandleMouse::IsValidPlacement(int gridX, int gridY) const
{
    // Check grid bounds
    if (gridX < 0 || gridX >= Grid::GetWidth() ||
        gridY < 0 || gridY >= Grid::GetHeight())
    {
        return false;
    }

    // Check if not an obstacle (valueId = 10) or spire (spriteId = 100)
    const Cell& cell = grid.GetCell(gridX, gridY);
    return (cell.valueId != 10 && cell.spriteId != spire.GetSpireId());
}

void HandleMouse::UpdateMouse()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();

        int gridX = GetGridX(static_cast<int>(mousePos.x));
        int gridY = GetGridY(static_cast<int>(mousePos.y));

        if (IsValidPlacement(gridX, gridY))
        {
            wall.PlaceWall(grid, gridX, gridY);
            enemySpawner.CalculatePaths(); // This method needs to be added to EnemySpawner
        }
    }
}