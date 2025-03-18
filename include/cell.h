#ifndef CELL_H
#define CELL_H

struct Cell
{
    int spriteId { 0 };
    int valueId { 0 };
    static constexpr double CELL_SIZE { 64 };
};

#endif //CELL_H