#include "grid.h"
#include "cell.h"
#include <stdexcept>
#include "profileScope.h"

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

    if (backgroundInitialized)
    {
        UnloadRenderTexture(backgroundTexture);
    }
}

void Grid::LoadTextures()
{
    for (int i = 0; i < MAX_GRID_TEXTURES; ++i)
    {
        // i+1 - S0 does not exist!
        std::string fileName = "../resources/background_tiles/s"
        + std::to_string(i + 1) + ".png";

        textures[i] = LoadTexture(fileName.c_str());
        SetTextureFilter(textures[i], TEXTURE_FILTER_POINT);
    }
}

void Grid::GenerateGrid()
{
    for (int y = 0; y < GRID_HEIGHT; ++y)
    {
        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            cells[x][y].spriteId = GetRandomValue(0, MAX_GRID_TEXTURES-1);
            cells[x][y].valueId = 1;
        }
    }
}

/* Instead of drawing our background every frame,
 * I wanted to make it static and draw it onto a render texture.
 */
void Grid::InitializeBackground()
{
    PROFILE_GRID("Initialize Background");

    backgroundTexture = LoadRenderTexture(GRID_WIDTH * Cell::CELL_SIZE, GRID_HEIGHT * Cell::CELL_SIZE);

    // Here, we importantly render the grid to the texture
    BeginTextureMode(backgroundTexture);
    ClearBackground(RAYWHITE);

    for (int y = 0; y < GRID_HEIGHT; ++y)
    {
        for (int x = 0; x < GRID_WIDTH; ++x)
        {
            int screenX = x * static_cast<int>(Cell::CELL_SIZE);
            int screenY = y * static_cast<int>(Cell::CELL_SIZE);

            DrawCellToTexture(cells[x][y].spriteId, screenX, screenY);
        }
    }

    EndTextureMode();
    backgroundInitialized = true;
}

void Grid::DrawCellToTexture(int id, int x, int y) const
{
    if (id >= 0 && id < MAX_GRID_TEXTURES && textures[id].id != 0)
    {
        Vector2 position = { static_cast<float>(x), static_cast<float>(y) };
        DrawTextureEx(textures[id], position, 0, 2.0f, WHITE);
    }
}

void Grid::DrawGrid() const
{
    PROFILE_GRID("DrawAllCells");

    if (!backgroundInitialized)
    {
        const_cast<Grid*>(this)->InitializeBackground();
    }

    DrawTextureRec
    (
        backgroundTexture.texture,
        { 0, 0, static_cast<float>(backgroundTexture.texture.width), -static_cast<float>(backgroundTexture.texture.height) },
        { 0, 0 },
        WHITE
    );
}

void Grid::DrawCell(int id, int x, int y) const
{
    if (id >= 0 && id < MAX_GRID_TEXTURES && textures[id].id != 0)
    {
        // In order to upscale the textures to 64 pixels, we need a vector for DrawTextureEx
        Vector2 position = { static_cast<float>(x), static_cast<float>(y) };

        // art 32x, render at 2x size
        DrawTextureEx(textures[id], position, 0, 2.0f, WHITE);
    }
}

void Grid::CheckBounds(int x, int y) const
{
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
    {
        throw std::out_of_range("Cell coordinates out of range");
    }
}

void Grid::UpdateBackgroundCell(int x, int y)
{
    if (!backgroundInitialized)
    {
        return;
    }

    BeginTextureMode(backgroundTexture);

    int screenX = x * static_cast<int>(Cell::CELL_SIZE);
    int screenY = y * static_cast<int>(Cell::CELL_SIZE);

    DrawCellToTexture(cells[x][y].spriteId, screenX, screenY);

    EndTextureMode();
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