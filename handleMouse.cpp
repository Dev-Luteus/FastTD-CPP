#include "handleMouse.h"
#include <raylib.h>

#include "game.h"
#include "gameCamera.h"

/* I hate this constructor ( beginner at c++ )
 */
HandleMouse::HandleMouse(
        Grid& grid, EnemySpawner& enemySpawner,
        Wall& wall, Spire& spire, GameCamera& camera, Player& player,
        RoundManager& roundManager, int screenWidth, int uiWidth)

    : grid(grid), enemySpawner(enemySpawner),
      wall(wall), spire(spire), camera(camera),
      player(player), roundManager(roundManager),
      SCREEN_WIDTH(screenWidth), UI_WIDTH(uiWidth)
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

bool HandleMouse::IsInsideUI(Vector2 mousePos) const
{
    return mousePos.x >= static_cast<float>(SCREEN_WIDTH - UI_WIDTH);
}

void HandleMouse::UpdateMouse()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();

        if (IsInsideUI(mousePos))
        {
            return;
        }

        Vector2 worldPos = GetScreenToWorld2D(mousePos, camera.GetCamera());

        int gridX = static_cast<int>(worldPos.x) / Cell::CELL_SIZE;
        int gridY = static_cast<int>(worldPos.y) / Cell::CELL_SIZE;

        if (IsValidPlacement(gridX, gridY))
        {
            bool wallPlaced = wall.PlaceWall(grid, player, roundManager, gridX, gridY);

            if (wallPlaced)
            {
                enemySpawner.CalculatePaths();
            }
        }
    }
}