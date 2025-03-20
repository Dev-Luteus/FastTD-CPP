#include "wall.h"
#include <stdexcept>

Wall::Wall()
    : texture{0}
{
}

Wall::~Wall()
{
    if (texture.id != 0)
    {
        UnloadTexture(texture);
    }
}

void Wall::LoadTextures()
{
    texture = LoadTexture("../resources/walls/wall1.png");

    if (texture.id == 0)
    {
        throw std::runtime_error("Failed to load wall texture");
    }
}

/* I decided to Store our wall positions, and then draw them in Game!
 */
void Wall::PlaceWall(Grid& grid, int gridX, int gridY)
{
    Cell& cell = grid.ModifyCell(gridX, gridY);
    cell.valueId = WALL_VALUE_ID;

    wallPositions.push_back({ gridX, gridY });
}

void Wall::DrawWalls() const
{
    if (texture.id != 0)
    {
        for (const auto& position : wallPositions)
        {
            float screenX = static_cast<float>(position.gridX * Cell::CELL_SIZE);
            float screenY = static_cast<float>(position.gridY * Cell::CELL_SIZE);

            Vector2 screenPosition = { screenX, screenY };

            DrawTextureEx(texture, screenPosition, 0, 2.0f, WHITE);
        }
    }
}