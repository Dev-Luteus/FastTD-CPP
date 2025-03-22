#ifndef WALL_H
#define WALL_H

#include "grid.h"
#include <raylib.h>
#include <vector>
#include "player.h"
#include "roundManager.h"

struct WallPosition
{
    int gridX;
    int gridY;
};

class Wall
{
private:
    static constexpr int WALL_VALUE_ID  { 10 };
    static constexpr int WALL_SPRITE_ID { 101 };
    static constexpr int WALL_COST { 10 };

    Texture2D texture;
    std::vector<WallPosition> wallPositions;

public:
    Wall();
    ~Wall();

    void LoadTextures();
    bool PlaceWall(Grid& grid, Player& player, RoundManager& roundManager, int gridX, int gridY);
    void DrawWalls() const;

    [[nodiscard]] int GetCost() { return WALL_COST; }
};

#endif //WALL_H