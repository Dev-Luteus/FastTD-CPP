#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <raylib.h>
#include "grid.h"
#include <vector>
#include "pathFinder.h"

/* Note to self, forward declare when:
 - Don't need to access its members or methods,
 - Only need to reference the class, or use pointers to it.
 - Otherwise good practice to avoid circular dependencies.
 */
class Enemy;

class Spire;

class EnemySpawner
{
private:
    static constexpr int ENEMY_SPAWNER_SIZE { 3 };
    static constexpr int ENEMY_SPAWNER_VALUE_ID { 10 };
    static constexpr float ENEMY_SPAWNER_INTERVAL { 5.0f }; // Every X seconds

    static constexpr float SPAWN_POINT_X { 1 };
    static constexpr float SPAWN_POINT_Y { 3 };

    Texture2D texture { 0 };
    int gridX { 0 };
    int gridY { 0 };

    /* vector = C++ dynamic array,
     * store pointers to Enemy objects, which allows us to create Enemies in the heap,
     * Store and manage enemies with different lifetimes,
     * etc
     */
    float spawnTimer { 0.0f };
    std::vector<Enemy*> enemies;

    // enemies
    PathFinder* pathFinder{nullptr}; // store as nullptr, initialize later

    int targetX { 0 };
    int targetY { 0 };
    bool hasTarget { false };

public:
    struct SpawnPoint
    {
        int x { 0 };
        int y { 0 };
    } spawnPoint;

    EnemySpawner();
    ~EnemySpawner();

    void LoadTextures();
    void PlaceSpawner(Grid& grid);
    void DrawSpawner() const;

    void Update(float deltaTime, Grid& grid, Spire& spire);
    void SpawnEnemies(Grid& grid);
    void DrawEnemies() const;

    void SetTarget(int x, int y);
    [[nodiscard]] bool HasTarget() const;

    std::vector<PathNode> CalculatePath(int startX, int startY) const;
    void CalculatePaths();
};

#endif //ENEMYSPAWNER_H
