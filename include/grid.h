﻿#ifndef GRID_H
#define GRID_H

#include <array>
#include <raylib.h>
#include "cell.h"

class Grid
{
private:
    static constexpr int MAX_GRID_TEXTURES { 11 };
    static constexpr int GRID_WIDTH { 21 };
    static constexpr int GRID_HEIGHT { 15 };

    void CheckBounds(int x, int y) const;
    void DrawCell(int id, int x, int y) const;

public:

    // Grid width containing Cell rows by height
    std::array<std::array<Cell, GRID_HEIGHT>, GRID_WIDTH> cells;
    std::array<Texture2D, MAX_GRID_TEXTURES> textures;

    Grid() = default;
    ~Grid(); // A de-constructor to unload our textures ^^!

    void LoadTextures();
    void GenerateGrid();
    void DrawGrid() const;

    [[nodiscard]] Cell& ModifyCell(int x, int y);
    [[nodiscard]] const Cell& GetCell(int x, int y) const;

    [[nodiscard]] static constexpr int GetWidth() { return GRID_WIDTH; }
    [[nodiscard]] static constexpr int GetHeight() { return GRID_HEIGHT; }
};

#endif //GRID_H