#ifndef MAP_H
#define MAP_H

#include <array>
#include "cell.h"
#include "grid.h"

class Obstacles
{
    private:
    static constexpr int MAX_OBSTACLES_TEXTURES { 10 };

    std::array<std::array<Cell, Grid::GRID_HEIGHT>, Grid::GRID_WIDTH> obstacles;
    std::array<Texture2D, Grid::GRID_WIDTH> obstacleTextures;

    public:
    void LoadTextures();
    void GenerateObstacles();
    void DrawObstacles();
};

#endif //MAP_H
