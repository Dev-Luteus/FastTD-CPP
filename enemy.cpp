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

        FollowPath();
    }
}

void Enemy::FollowPath()
{
    if (!path.empty() && currentPathIndex < path.size())
    {
        gridX = path[currentPathIndex].x;
        gridY = path[currentPathIndex].y;

        currentPathIndex++;
    }
}

void Enemy::Draw() const
{
    if (texture.id != 0)
    {
        auto screenX = static_cast<float>(gridX * Cell::CELL_SIZE);
        auto screenY = static_cast<float>(gridY * Cell::CELL_SIZE);

        Vector2 position = { screenX, screenY };

        // 32x, 38y ( bad but works)
        DrawTextureEx(texture, position, 0, 2.0f, WHITE);
    }
}

void Enemy::SetPath(const std::vector<PathNode> &newPath)
{
    path = newPath; // calculated path
    currentPathIndex = 0;

    if (!newPath.empty())
    {
        const PathNode& destination = newPath.back(); // .back() = final destination!
        targetGridX = destination.x;
        targetGridY = destination.y;
    }
}

bool Enemy::HasReachedGoal() const
{
    return path.empty() || currentPathIndex >= path.size();
}
