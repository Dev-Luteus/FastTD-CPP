#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include "grid.h"

class Enemy
{
private:
    static constexpr float MOVE_SPEED { 1.0f }; // X cell per second

    Texture2D texture;
    int gridX;
    int gridY;
    float movementTimer { 0.0f };

    int targetGridX;
    int targetGridY;

public:
    Enemy(int startX, int startY);
    ~Enemy();

    void LoadTextures();
    void Update(float deltaTime, Grid& grid);
    void Draw() const;

    // Method to set the next target position
    // You'll implement A* pathfinding to determine this target
    void SetNextTarget(int x, int y);

    // Get current grid position
    [[nodiscard]] int GetGridX() const { return gridX; }
    [[nodiscard]] int GetGridY() const { return gridY; }
};

#endif //ENEMY_H
