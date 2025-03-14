#include "grid.h"
#include "cell.h"
#include <stdexcept>

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

void Grid::DrawGrid() // in the works
{

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