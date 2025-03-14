#include "grid.h"
#include "cell.h"
#include <stdexcept>

Grid::~Grid()
{
    for (int i = 0; i < MAX_TEXTURES; ++i)
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
    // Cell.id, not texture.id
    textures[0] = LoadTexture("../resources/stone_tiles/s1.png");
    textures[1] = LoadTexture("../resources/stone_tiles/s2.png");
    textures[2] = LoadTexture("../resources/stone_tiles/s3.png");
    textures[3] = LoadTexture("../resources/stone_tiles/s4.png");
}


void Grid::GenerateGrid()
{
    for (int y = 0; y < GRID_HEIGHT; ++y)
    {
        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            cells[x][y].id = 0;
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
    if (id >= 0 && id < MAX_TEXTURES && textures[id].id != 0)
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