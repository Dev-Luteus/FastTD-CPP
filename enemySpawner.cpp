#include "enemySpawner.h"
#include <stdexcept>
#include "enemy.h"

EnemySpawner::~EnemySpawner()
{
    if (texture.id != 0)
    {
        UnloadTexture(texture);
    }

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

    spawnPoint.x = gridX + 1;
    spawnPoint.y = gridY + 2;

    grid.ModifyCell(spawnPoint.x, spawnPoint.y).valueId = ENEMY_SPAWNER_VALUE_ID;
}


void EnemySpawner::DrawSpawner() const
{
    if (texture.id != 0)
    {
        float screenX = gridX * Cell::CELL_SIZE;
        float screenY = gridY * Cell::CELL_SIZE;

        Vector2 position = { screenX, screenY };
        DrawTextureEx(texture, position, 0, 2.0f, WHITE);
    }
}

void EnemySpawner::Update(float deltaTime, Grid &grid)
{
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
        enemy->Update(deltaTime, grid);

        //TODO: Check if enemy is out of bounds or dead
    }
}

void EnemySpawner::SpawnEnemies(Grid &grid)
{
    Enemy* enemy = new Enemy(spawnPoint.x, spawnPoint.y);
    enemies.push_back(enemy); // Add enemy to the list

    //TODO: A* agent target = enemy->SetNextTarget
}

void EnemySpawner::DrawEnemies() const
{
    for (const Enemy* enemy : enemies)
    {
        enemy->Draw();
    }
}