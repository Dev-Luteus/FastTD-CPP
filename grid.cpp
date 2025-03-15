#include "grid.h"
#include "cell.h"
#include <stdexcept>

Grid::~Grid()
{
    for (int i = 0; i < MAX_GRID_TEXTURES; ++i)
    {
        /* Raylib assigns a non-zero value to a texture, if it's been successfully loaded ->
         * -> into gpu memory, meaning we can easily check this!
         */
        if (textures[i].id != 0)
        {
            UnloadTexture(textures[i]);
        }
    }
}

void Grid::LoadTextures()
{
    // We have 9 textures, S1 to S9.
    for (int i = 0; i < MAX_GRID_TEXTURES; ++i)
    {
        std::string fileName = "../resources/stone_tiles/s" + std::to_string(i + 1) + ".png"; // i+1 - S0 does not exist!

        textures[i] = LoadTexture(fileName.c_str());
    }
}

void Grid::GenerateGrid()
{
    for (int y = 0; y < GRID_HEIGHT; ++y)
    {
        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            cells[x][y].id = GetRandomValue(0, 8);
        }
    }
}

void Grid::DrawGrid() const
{
    for (int y = 0; y < GRID_HEIGHT; ++y)
    {
        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            int screenX = x * Cell::CELL_SIZE;
            int screenY = y * Cell::CELL_SIZE;

            DrawCell(cells[x][y].id, screenX, screenY);
        }
    }
}

void Grid::DrawCell(int id, int x, int y) const
{
    if (id >= 0 && id < MAX_GRID_TEXTURES && textures[id].id != 0)
    {
        DrawTexture(textures[id], x, y, WHITE);
    }
}

void Grid::CheckBounds(int x, int y) const
{
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
    {
        throw std::out_of_range("Cell coordinates out of range");
    }
}

Cell &Grid::ModifyCell(int x, int y)
{
    CheckBounds(x, y);
    return cells[x][y];
}

const Cell& Grid::GetCell(int x, int y) const
{
    CheckBounds(x, y);
    return cells[x][y];
}