#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <raylib.h>
#include "grid.h"
#include <vector>

/* Note to self, forward declare when:
 - Don't need to access its members or methods,
 - Only need to reference the class, or use pointers to it.
 - Otherwise good practice to avoid circular dependencies.
 */
class Enemy;

class EnemySpawner
{
private:
    static constexpr int ENEMY_SPAWNER_SIZE { 4 };
    static constexpr int ENEMY_SPAWNER_VALUE_ID { 10 };
    static constexpr float ENEMY_SPAWNER_INTERVAL { 3.0f }; // Every X seconds

    Texture2D texture;
    int gridX;
    int gridY;

    /* vector = C++ dynamic array,
     * store pointers to Enemy objects, which allows us to create Enemies in the heap,
     * Store and manage enemies with different lifetimes,
     * etc
     */
    float spawnTimer { 0.0f };
    std::vector<Enemy*> enemies;

public:
    struct SpawnPoint
    {
        int x;
        int y;
    } spawnPoint;

    EnemySpawner() = default;
    ~EnemySpawner();

    void LoadTextures();
    void PlaceSpawner(Grid& grid);
    void DrawSpawner() const;

    void Update(float deltaTime, Grid& grid);
    void SpawnEnemies(Grid& grid);
    void DrawEnemies() const;
};

#endif //ENEMYSPAWNER_H
