#ifndef WALL_H
#define WALL_H

#include "grid.h"
#include <raylib.h>
#include <vector>

struct WallPosition
{
    int gridX;
    int gridY;
};

class Wall
{
private:
    static constexpr int WALL_VALUE_ID = 10;
    static constexpr int WALL_SPRITE_ID = 101;

    Texture2D texture;
    std::vector<WallPosition> wallPositions;

public:
    Wall();
    ~Wall();

    void LoadTextures();
    void PlaceWall(Grid& grid, int gridX, int gridY);
    void DrawWalls() const;
};

#endif //WALL_H