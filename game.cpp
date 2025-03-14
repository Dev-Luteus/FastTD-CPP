#include "raylib.h"
#include "game.h"

#include "grid.h"

void Game::Initialize()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FastTD");
    SetTargetFPS(60);

    grid.LoadTextures();
    grid.GenerateGrid();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        Game::Draw();
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    grid.DrawGrid();

    EndDrawing();
}

void Game::Shutdown()
{
    CloseWindow();
}
