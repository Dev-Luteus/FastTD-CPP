#include "enemy.h"
#include <stdexcept>

Enemy::Enemy(int startX, int startY)
    : gridX(startX), gridY(startY), targetGridX(startX), targetGridY(startY)
{
    LoadTextures();
}

Enemy::~Enemy()
{
    if (texture.id != 0)
    {
        UnloadTexture(texture);
    }
}

void Enemy::LoadTextures()
{
    texture = LoadTexture("../resources/enemies/skeleton_walk1.png");

    if (texture.id == 0)
    {
        throw std::runtime_error("Failed to load enemy texture");
    }
}

void Enemy::Update(float deltaTime, Grid &grid)
{
    movementTimer += deltaTime;

    while (movementTimer >= MOVE_SPEED)
    {
        movementTimer = 0.0f;

        // A* Agent Pathfinding
    }
}

void Enemy::Draw() const
{
    if (texture.id != 0)
    {
        float screenX = gridX * Cell::CELL_SIZE;
        float screenY = gridY * Cell::CELL_SIZE;

        Vector2 position = { screenX, screenY };
        DrawTextureEx(texture, position, 0, 2.0f, WHITE);
    }
}

void Enemy::SetNextTarget(int x, int y)
{
    targetGridX = x;
    targetGridY = y;
}