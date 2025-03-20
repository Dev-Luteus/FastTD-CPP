#include "obstacles.h"
#include <string>

#include "handleMouse.h"

Obstacles::~Obstacles()
{
    for (int i = 0; i < OBSTACLES_MAX_TEXTURES; ++i)
    {
        if (obstacleTextures[i].id != 0)
        {
            UnloadTexture(obstacleTextures[i]);
        }
    }
}

void Obstacles::LoadTextures()
{
    for (int i = 0; i < OBSTACLES_MAX_TEXTURES; ++i)
    {
        std::string fileName = "../resources/obstacles/o" + std::to_string(i+1) + ".png";
        obstacleTextures[i] = LoadTexture(fileName.c_str());
    }
}

/* A simple helper method that validates the cells we place our obstacles on.
 * I set the spire to 0, and the background cells to 1, so we just check its valueId!
 * We then set the id of obstacles to 10, and use this id as padding between obstacles.
 */
bool Obstacles::IsPositionValid(int x, int y, const Grid& grid) const
{
    if (x < 0 || y < 0 ||
        x + OBSTACLES_PADDING + OBSTACLES_PADDING > Grid::GetWidth() ||
        y + OBSTACLES_PADDING + OBSTACLES_PADDING > Grid::GetHeight())
    {
        return false;
    }

    for (int dy = 0; dy < OBSTACLE_SIZE; ++dy)
    {
        for (int dx = 0; dx < OBSTACLE_SIZE; ++dx)
        {
            if (grid.GetCell(x + dx, y + dy).valueId != 1)
            {
                return false;
            }
        }
    }

    // If obstacle too close, false
    for (int checkY = y - OBSTACLES_PADDING; checkY < y + OBSTACLE_SIZE + OBSTACLES_PADDING; checkY++)
    {
        for (int checkX = x - OBSTACLES_PADDING; checkX < x + OBSTACLE_SIZE + OBSTACLES_PADDING; checkX++)
        {
            // Skip placement area
            if (checkX >= x && checkX < x + OBSTACLE_SIZE &&
                checkY >= y && checkY < y + OBSTACLE_SIZE)
            {
                continue;
            }

            // bounds check ( necessary, it crashed without )
            if (checkX < 0 || checkX >= Grid::GetWidth() ||
                checkY < 0 || checkY >= Grid::GetHeight())
            {
                continue;
            }

            if (grid.GetCell(checkX, checkY).valueId == OBSTACLES_VALUE_ID)
            {
                return false;
            }
        }
    }

    return true;
}

/* Our main method for obstacle placement.
 * To make it more efficient, I wanted to try shifting objects into new positions.
 * I tried doing this in a simple way but nothing really changed.
 *
 * Henceforth, I re-used principles I had done in my previous DungeonRogue-C game:
 * - Where we make a dirX and dirY for directional-pattern-searching!
 */
bool Obstacles::BoundsPadding(int& x, int& y, const Grid& grid) const
{
    if (IsPositionValid(x, y, grid))
    {
        return true;
    }

    // random directions
    const int dirX[8] = {1, 0, -1, 0, 1, 1, -1, -1};
    const int dirY[8] = {0, 1, 0, -1, -1, 1, 1, -1};

    const int maxShift = OBSTACLES_PADDING*4;

    for (int shift = 1; shift <= maxShift; shift++)
    {
        for (int dir = 0; dir < 8; dir++)
        {
            int newX = x + (shift * dirX[dir]);
            int newY = y + (shift * dirY[dir]);

            if (newX >= 0 && newX + OBSTACLE_SIZE <= Grid::GetWidth() &&
                newY >= 0 && newY + OBSTACLE_SIZE <= Grid::GetHeight() &&
                IsPositionValid(newX, newY, grid))
            {
                x = newX;
                y = newY;
                return true;
            }
        }
    }

    return false;
}

void Obstacles::GenerateObstacles(Grid& grid)
{
    obstaclePositions.clear();

    int placedObstacles = 0;
    int failedAttempts = 0;
    const int maxFailedAttempts = 10000;

    while (placedObstacles < OBSTACLES_MAX_AMOUNT && failedAttempts < maxFailedAttempts)
    {
        int x = GetRandomValue(0, Grid::GetWidth() - OBSTACLE_SIZE);
        int y = GetRandomValue(0, Grid::GetHeight() - OBSTACLE_SIZE);

        if (BoundsPadding(x, y, grid))
        {
            int textureId = GetRandomValue(0, OBSTACLES_MAX_TEXTURES - 1);

            for (int dy = 0; dy < OBSTACLE_SIZE; ++dy)
            {
                for (int dx = 0; dx < OBSTACLE_SIZE; ++dx)
                {
                    Cell& cell = grid.ModifyCell(x + dx, y + dy);
                    cell.valueId = OBSTACLES_VALUE_ID;
                    cell.spriteId = textureId;
                }
            }

            // Store obstacle
            ObstaclePos obstacle;
            obstacle.x = x;
            obstacle.y = y;
            obstacle.textureId = textureId;
            obstaclePositions.push_back(obstacle);

            placedObstacles++;
            failedAttempts = 0;
        }
        else
        {
            failedAttempts++;
        }
    }
}

void Obstacles::DrawObstacles() const
{
    // Essentially a for-each loop! (Learning C++ syntax)
    for (const ObstaclePos& obstacle : obstaclePositions)
    {
        float screenX = obstacle.x * Cell::CELL_SIZE;
        float screenY = obstacle.y * Cell::CELL_SIZE;

        Vector2 position = { screenX, screenY };

        SetTextureFilter(obstacleTextures[obstacle.textureId], TEXTURE_FILTER_POINT);
        DrawTextureEx(obstacleTextures[obstacle.textureId], position, 0, 2.0f, WHITE);
    }
}