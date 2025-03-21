#ifndef MAP_H
#define MAP_H

#include <array>
#include <vector>
#include "grid.h"

struct ObstaclePos
{
    int x;
    int y;
    int textureId;
};

// This Obstacle code definitely sucks. But I only need a simple implementation for now
class Obstacles
{
private:
    static constexpr int OBSTACLES_MAX_TEXTURES { 4 };
    static constexpr int OBSTACLES_MAX_AMOUNT { 20 };
    static constexpr int OBSTACLE_SIZE { 2 }; // 2x2
    static constexpr int OBSTACLES_PADDING { 4 };
    static constexpr int OBSTACLES_VALUE_ID { 10 };

    std::array<Texture2D, OBSTACLES_MAX_TEXTURES> obstacleTextures;
    std::vector<ObstaclePos> obstaclePositions;

    [[nodiscard]] bool IsPositionValid(int x, int y, const Grid& grid) const;
    bool BoundsPadding(int& x, int& y, const Grid& grid) const;

public:
    Obstacles() = default;
    ~Obstacles();

    void LoadTextures();
    void GenerateObstacles(Grid& grid);
    void DrawObstacles() const;

    [[nodiscard]] bool GetObstacleValueId() { return OBSTACLES_VALUE_ID; }
};

#endif //MAP_H