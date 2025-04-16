#include "wall.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "player.h"
#include "roundManager.h"

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

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

/* I decided to Store our wall positions, and then draw them in Game!
 */
bool Wall::PlaceWall(Grid& grid, Player& player, RoundManager& roundManager, int gridX, int gridY)
{
    if (roundManager.GetRoundState() != RoundManager::BUILDING)
    {
        return false;
    }

    if (player.GetCurrency() < WALL_COST)
    {
        return false;
    }

    player.SetCurrency(-WALL_COST);
    std::cout << "Player Currency: " << player.GetCurrency() << std::endl;

    Cell& cell = grid.ModifyCell(gridX, gridY);
    cell.valueId = WALL_VALUE_ID;
    grid.UpdateBackgroundCell(gridX, gridY); // updating visuals
    wallPositions.push_back({ gridX, gridY });

    return true;
}

void Wall::DrawWalls() const
{
    if (texture.id != 0)
    {
        for (const auto& position : wallPositions)
        {
            auto screenX = static_cast<float>(position.gridX * Cell::CELL_SIZE);
            auto screenY = static_cast<float>(position.gridY * Cell::CELL_SIZE);

            Vector2 screenPosition = { screenX, screenY };

            DrawTextureEx(texture, screenPosition, 0, 2.0f, WHITE);
        }
    }
}