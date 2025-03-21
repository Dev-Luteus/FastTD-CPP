#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include "grid.h"
#include "pathNode.h"
#include "spire.h"

class Enemy
{
private:
    static constexpr float ENEMY_MOVE_SPEED { 1.0f }; // X cell per second
    static constexpr int ENEMY_DAMAGE { 5 };

    Texture2D texture { 0 };
    int gridX;
    int gridY;
    int lastGridX;
    int lastGridY;
    float movementTimer { 0.0f };
    float lerpAmount { 0.0f };

    // Path
    std::vector<PathNode> path; // store final path
    size_t currentPathIndex { 0 }; // size_t for convenience

    int targetGridX;
    int targetGridY;

public:
    Enemy(int startX, int startY);
    ~Enemy();

    void LoadTextures();
    void Update(float deltaTime, Grid& grid, Spire& spire);
    void Draw() const;

    void SetPath(const std::vector<PathNode>& newPath);
    void FollowPath();
    void Attack(Spire& spire);

    [[nodiscard]] float GetLerpedX() const;
    [[nodiscard]] float GetLerpedY() const;
    [[nodiscard]] bool HasReachedGoal() const;
    [[nodiscard]] int GetGridX() const { return gridX; }
    [[nodiscard]] int GetGridY() const { return gridY; }
};

#endif //ENEMY_H
