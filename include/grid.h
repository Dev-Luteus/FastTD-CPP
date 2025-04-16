#ifndef GRID_H
#define GRID_H

#include <array>
#include <raylib.h>
#include "cell.h"

class Grid
{
    static constexpr int MAX_GRID_TEXTURES { 11 };
    static constexpr int GRID_WIDTH { 41 };
    static constexpr int GRID_HEIGHT { 41 };
    static constexpr int VISIBLE_GRID_WIDTH { 25 };
    static constexpr int VISIBLE_GRID_HEIGHT { 17 };

    RenderTexture2D backgroundTexture { };
    bool backgroundInitialized = false;

    void CheckBounds(int x, int y) const;
    void DrawCell(int id, int x, int y) const;
    void DrawCellToTexture(int id, int x, int y) const;

public:
    // Grid width containing Cell rows by height
    std::array<std::array<Cell, GRID_HEIGHT>, GRID_WIDTH> cells { };
    std::array<Texture2D, MAX_GRID_TEXTURES> textures { };

    Grid() : backgroundTexture{}, backgroundInitialized(false), cells{}, textures{} { }
    ~Grid(); // A de-constructor to unload our textures ^^!

    void LoadTextures();
    void GenerateGrid();
    void InitializeBackground();
    void DrawGrid() const;

    // function to update the now pre-rendered background
    void UpdateBackgroundCell(int x, int y);

    [[nodiscard]] Cell& ModifyCell(int x, int y);
    [[nodiscard]] const Cell& GetCell(int x, int y) const;

    [[nodiscard]] static constexpr int GetWidth() { return GRID_WIDTH; }
    [[nodiscard]] static constexpr int GetHeight() { return GRID_HEIGHT; }
    [[nodiscard]] static constexpr int GetVisibleWidth() { return VISIBLE_GRID_WIDTH; }
    [[nodiscard]] static constexpr int GetVisibleHeight() { return VISIBLE_GRID_HEIGHT; }
};

#endif //GRID_H