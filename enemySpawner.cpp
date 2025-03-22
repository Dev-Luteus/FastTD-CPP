﻿#include "enemySpawner.h"
#include <stdexcept>
#include "enemy.h"
#include "roundManager.h"

EnemySpawner::EnemySpawner()
    : texture{0}, gridX{0}, gridY{0}, spawnTimer{0.0f},
      pathFinder{nullptr}, targetX{0}, targetY{0}, hasTarget{false}
{
    spawnPoint.x = 0;
    spawnPoint.y = 0;
}

EnemySpawner::~EnemySpawner()
{
    if (texture.id != 0)
    {
        UnloadTexture(texture);
    }

    delete pathFinder;
    pathFinder = nullptr;

    for (Enemy* enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
}

void EnemySpawner::LoadTextures()
{
    texture = LoadTexture("../resources/enemy_spawner/enemy_spawner.png");

    if (texture.id == 0)
    {
        throw std::runtime_error("Failed to load enemy spawner texture");
    }
}

void EnemySpawner::PlaceSpawner(Grid& grid)
{
    gridX = 0;
    gridY = 0;

    for (int y = 0; y < ENEMY_SPAWNER_SIZE; ++y)
    {
        for (int x = 0; x < ENEMY_SPAWNER_SIZE; ++x)
        {
            grid.ModifyCell(gridX + x, gridY + y).valueId = ENEMY_SPAWNER_VALUE_ID;
        }
    }

    spawnPoint.x = SPAWN_POINT_X;
    spawnPoint.y = SPAWN_POINT_Y;

    grid.ModifyCell(spawnPoint.x, spawnPoint.y).valueId = ENEMY_SPAWNER_VALUE_ID;

    // Initialize our pathfinder!
    if (pathFinder == nullptr)
    {
        pathFinder = new PathFinder(grid);
    }
}

void EnemySpawner::DrawSpawner() const
{
    if (texture.id != 0)
    {
        auto screenX = static_cast<float>(gridX * Cell::CELL_SIZE);
        auto screenY = static_cast<float>(gridY * Cell::CELL_SIZE);

        Vector2 position = { screenX, screenY };

        DrawTextureEx(texture, position, 0, 2.0f, WHITE);
    }
}

void EnemySpawner::Update(float deltaTime, Grid &grid, Spire& spire, RoundManager& roundManager)
{
    if (roundManager.GetRoundState() != RoundManager::DEFENDING)
    {
        return;
    }

    spawnTimer += deltaTime;

    if (spawnTimer >= ENEMY_SPAWNER_INTERVAL)
    {
        SpawnEnemies(grid);
        spawnTimer = 0.0f;
    }

    /* Iterator loop: iterates the Enemy vector enemies,
     * auto it = enemies.begin() :
     * 1. => Create an iterator, it, that points to the first element of the enemies vector,
     * 2. begin() => Returns an iterator pointing to the first element of the vector,
     *
     * it != enemies.end() :
     * 1. Iterate to the end,
     * 2. end() => Returns an iterator pointing to the last element of the vector,
     */
    for (auto it = enemies.begin(); it != enemies.end(); ++it)
    {
        /* Enemy* enemy = *it:
         * *it : Dereference the iterator to get the Enemy pointer,
         * enemy : Assign the pointer to the enemy variable,
         */
        Enemy* enemy = *it;
        enemy->Update(deltaTime, grid, spire);

        // for now, all of this ( attack etc ) is in Enemy.cpp. Not sure if I need this if statement yet
        // if (enemy->HasReachedGoal())
        // {
        //     //enemy->Attack();
        // }
    }
}

void EnemySpawner::SpawnEnemies(Grid &grid)
{
    auto* enemy = new Enemy(spawnPoint.x, spawnPoint.y);

    if (hasTarget && pathFinder != nullptr)
    {
        // Calculate path
        std::vector<PathNode> path = CalculatePath(spawnPoint.x, spawnPoint.y);

        if (!path.empty())
        {
            // give path
            enemy->SetPath(path);
            enemies.push_back(enemy);
        }
        else
        {
            printf("No path found for enemy from (%d, %d) to (%d, %d)\n",
                   spawnPoint.x, spawnPoint.y, targetX, targetY);
        }
    }
}

std::vector<PathNode> EnemySpawner::CalculatePath(int startX, int startY) const
{
    if (hasTarget && pathFinder != nullptr)
    {
        return pathFinder->FindPath(startX, startY, targetX, targetY);
    }

    return {}; // List initialization, returns empty node!
}

void EnemySpawner::CalculatePaths()
{
    if (!hasTarget || pathFinder == nullptr)
    {
        return;
    }

    for (Enemy* enemy : enemies)
    {
        if (!enemy->HasReachedGoal())
        {
            int currentX = enemy->GetGridX();
            int currentY = enemy->GetGridY();

            std::vector<PathNode> path = CalculatePath(currentX, currentY);

            if (!path.empty())
            {
                enemy->SetPath(path);
            }
            else
            {
                printf("No path found for enemy from (%d, %d) to (%d, %d) after wall placement\n",
                       currentX, currentY, targetX, targetY);
            }
        }
    }
}

void EnemySpawner::SetTarget(int x, int y)
{
    targetX = x; targetY = y; hasTarget = true;
}

bool EnemySpawner::HasTarget() const
{
    return hasTarget;
}

void EnemySpawner::DrawEnemies() const
{
    for (const Enemy* enemy : enemies)
    {
        enemy->Draw();
    }
}