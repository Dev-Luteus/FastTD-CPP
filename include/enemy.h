#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include "grid.h"
#include "pathNode.h"

class Enemy
{
private:
    static constexpr float MOVE_SPEED { 1.0f }; // X cell per second

    Texture2D texture { 0 };
    int gridX;
    int gridY;
    float movementTimer { 0.0f };

    std::vector<PathNode> path; // store final path
    size_t currentPathIndex { 0 }; // size_t for conveinence

    int targetGridX;
    int targetGridY;

public:
    Enemy(int startX, int startY);
    ~Enemy();

    void LoadTextures();
    void Update(float deltaTime, Grid& grid);
    void Draw() const;

    void SetPath(const std::vector<PathNode>& newPath);
    void FollowPath();

    [[nodiscard]] bool HasReachedGoal() const;
    [[nodiscard]] int GetGridX() const { return gridX; }
    [[nodiscard]] int GetGridY() const { return gridY; }
};

#endif //ENEMY_H
