#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include "grid.h"
#include "pathNode.h"
#include "spire.h"

class Enemy
{
private:
    static constexpr float ENEMY_MOVE_SPEED { 0.5f }; // X cell per second ( lower value = faster )
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

    bool isDead { false };

public:
    Enemy(int startX, int startY);
    ~Enemy();

    void LoadTextures();
    void Update(float deltaTime, Grid& grid, Spire& spire);
    void Draw() const;
    void Attack(Spire& spire);

    void SetPath(const std::vector<PathNode>& newPath);
    void FollowPath();

    // To fix enemies teleporting
    bool CanRecalculatePath() const
    {
        return lerpAmount >= 0.99f || lerpAmount == 0.0f;
    }
    void RecalculatePath(const std::vector<PathNode>& newPath);

    [[nodiscard]] float GetLerpedX() const;
    [[nodiscard]] float GetLerpedY() const;
    [[nodiscard]] bool HasReachedGoal() const;
    [[nodiscard]] int GetGridX() const { return gridX; }
    [[nodiscard]] int GetGridY() const { return gridY; }

    void MarkAsDead() { isDead = true; }
    [[nodiscard]] bool IsDead() const { return isDead; }
};

#endif //ENEMY_H
