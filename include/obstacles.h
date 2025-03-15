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

class Obstacles
{
private:
    static constexpr int OBSTACLES_MAX_TEXTURES { 4 };
    static constexpr int OBSTACLES_MAX_AMOUNT { 12 };
    static constexpr int OBSTACLE_SIZE { 2 }; // 2x2
    static constexpr int OBSTACLES_PADDING { 2 };

    std::array<Texture2D, OBSTACLES_MAX_TEXTURES> obstacleTextures;
    std::vector<ObstaclePos> obstaclePositions;

    bool IsPositionValid(int x, int y, const Grid& grid) const;
    bool BoundsPadding(int& x, int& y, const Grid& grid) const;

public:
    Obstacles() = default;
    ~Obstacles();

    void LoadTextures();
    void GenerateObstacles(Grid& grid);
    void DrawObstacles() const;
};

#endif //MAP_H