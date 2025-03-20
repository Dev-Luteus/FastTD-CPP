#ifndef WALL_H
#define WALL_H

class Wall
{
private:
    static constexpr int WALL_VALUE_ID = { 10 };
    static constexpr int WALL_SPRITE_ID = { 101 };

public:
    void PlaceWall(int gridX, int gridY);
};

#endif //WALL_H

