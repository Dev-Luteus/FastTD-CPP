#include "raylib.h"
#include "game.h"

void Game::initialize()
{
    InitWindow(screenWidth, screenHeight, "FastTD");
    SetTargetFPS(60);
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        Game::draw();
    }
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
}

void Game::shutdown()
{
    CloseWindow();
}
