#ifndef GRID_H
#define GRID_H

#include <array>
#include "cell.h"

class Grid
{
    private:
    static constexpr int GRID_WIDTH { 40 };
    static constexpr int GRID_HEIGHT { 40 };

    // Grid width containing Cell rows by height
    std::array<std::array<Cell, GRID_HEIGHT>, GRID_WIDTH> cells;

    void CheckBounds(int x, int y) const;

    public:
    void GenerateGrid();
    void DrawGrid();

    [[nodiscard]] Cell& ModifyCell(int x, int y);
    [[nodiscard]] const Cell& GetCell(int x, int y) const;

    [[nodiscard]] static constexpr int GetWidth() { return GRID_WIDTH; }
    [[nodiscard]] static constexpr int GetHeight() { return GRID_HEIGHT; }
};

#endif //GRID_H