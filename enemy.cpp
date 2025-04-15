#include "enemy.h"
#include <stdexcept>

#include "profileScope.h"
#include "spire.h"

Enemy::Enemy(int startX, int startY)
    : gridX(startX), gridY(startY), lastGridX(startX), lastGridY(startY), 
      targetGridX(startX), targetGridY(startY)
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

void Enemy::Update(float deltaTime, Grid &grid, Spire& spire)
{
    PROFILE_ENEMY("Update");

    movementTimer += deltaTime;
    lerpAmount = movementTimer / ENEMY_MOVE_SPEED;

    if (lerpAmount > 1.0f)
    {
        lerpAmount = 1.0f;

        if (!HasReachedGoal())
        {
            // Here, we update our last position for lerping =)
            lastGridX = gridX;
            lastGridY = gridY;

            {
                PROFILE_ENEMY("FollowPath");
                FollowPath();
            }
            movementTimer = 0.0f;
            lerpAmount = 0.0f;
        }
        
        if (HasReachedGoal())
        {
            PROFILE_ENEMY("Attack");
            Attack(spire);
        }
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

void Enemy::Attack(Spire& spire)
{
    spire.ModifyHealth(ENEMY_DAMAGE);
    MarkAsDead();
}

float Enemy::GetLerpedX() const
{
    return static_cast<float>(lastGridX) + (gridX - lastGridX) * lerpAmount;
}

float Enemy::GetLerpedY() const
{
    return static_cast<float>(lastGridY) + (gridY - lastGridY) * lerpAmount;
}

void Enemy::Draw() const
{
    PROFILE_ENEMY("Draw");

    if (texture.id != 0)
    {
        float lerpedX = GetLerpedX();
        float lerpedY = GetLerpedY();
        
        // Grid -> screen coordinates ( auto cause compiler complained )
        auto screenX = static_cast<float>(lerpedX * Cell::CELL_SIZE);
        auto screenY = static_cast<float>(lerpedY * Cell::CELL_SIZE);

        Vector2 position = { screenX, screenY };

        // 32x, 38y ( bad but works)
        SetTextureFilter(texture, TEXTURE_FILTER_POINT);
        DrawTextureEx(texture, position, 0, 2.0f, WHITE);
    }
}

void Enemy::SetPath(const std::vector<PathNode> &newPath)
{
    path = newPath; // calculated path
    currentPathIndex = 0;

    // Setting to 0.9 to speed up movement after spawning ( bug after lerping )
    movementTimer = ENEMY_MOVE_SPEED * 0.9f;
    lerpAmount = 0.9f;

    if (!newPath.empty())
    {
        lastGridX = gridX;
        lastGridY = gridY;

        if (currentPathIndex < path.size())
        {
            gridX = path[currentPathIndex].x;
            gridY = path[currentPathIndex].y;
            currentPathIndex++;
        }

        const PathNode &destination = newPath.back(); // .back() = final destination!
        targetGridX = destination.x;
        targetGridY = destination.y;
    }
}

void Enemy::RecalculatePath(const std::vector<PathNode>& newPath)
{
    if (newPath.empty())
    {
        return;
    }

    int currentX = gridX;
    int currentY = gridY;

    // Recalculate
    size_t closestNodeIndex = 0;
    int minDistance = INT_MAX;

    for (size_t i = 0; i < newPath.size(); i++)
    {
        int dx = newPath[i].x - currentX;
        int dy = newPath[i].y - currentY;
        int distance = dx * dx + dy * dy;

        if (distance < minDistance)
        {
            minDistance = distance;
            closestNodeIndex = i;
        }
    }

    path = newPath;
    currentPathIndex = closestNodeIndex;

    if (currentX != newPath[closestNodeIndex].x || currentY != newPath[closestNodeIndex].y)
    {
        lastGridX = currentX;
        lastGridY = currentY;
        gridX = newPath[closestNodeIndex].x;
        gridY = newPath[closestNodeIndex].y;
        movementTimer = 0.0f;
        lerpAmount = 0.0f;
    }

    const PathNode &destination = newPath.back();
    targetGridX = destination.x;
    targetGridY = destination.y;
}

bool Enemy::HasReachedGoal() const
{
    return path.empty() || currentPathIndex >= path.size();
}