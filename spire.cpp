#include "spire.h"

Spire::~Spire()
{
    if (texture.id != 0)
    {
        UnloadTexture(texture);
    }
}

void Spire::LoadTextures()
{
    texture = LoadTexture("../resources/spire/spire.png");
}

void Spire::PlaceInCenter(Grid& grid)
{
    gridX = Grid::GetWidth() / 2 - SPIRE_SIZE / 2;
    gridY = Grid::GetHeight() / 2 - SPIRE_SIZE / 2;

    for (int y = 0; y < SPIRE_SIZE; ++y)
    {
        for (int x = 0; x < SPIRE_SIZE; ++x)
        {
            grid.ModifyCell(gridX + x, gridY + y).spriteId = SPIRE_SPRITE_ID;
            grid.ModifyCell(gridX + x, gridY + y).valueId = 0;
        }
    }
}

void Spire::Draw() const
{
    if (texture.id != 0)
    {
        float screenX = gridX * Cell::CELL_SIZE;
        float screenY = gridY * Cell::CELL_SIZE;

        Vector2 position = { screenX, screenY };
        DrawTextureEx(texture, position, 0, 2.0f, WHITE);
    }
}

int Spire::GetCenterX() const
{
    return gridX + SPIRE_SIZE / 2;
}

int Spire::GetCenterY() const
{
    return gridY + SPIRE_SIZE / 2;
}
