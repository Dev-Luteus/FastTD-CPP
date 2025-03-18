#include "raylib.h"
#include "game.h"

void Game::Initialize()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FastTD");
    SetTargetFPS(60);

    grid.LoadTextures();
    grid.GenerateGrid();

    spire.LoadTextures();
    spire.PlaceInCenter(grid);

    enemy_spawner.LoadTextures();
    enemy_spawner.PlaceSpawner(grid);
    enemy_spawner.SetTarget(spire.GetCenterX(), spire.GetCenterY());

    obstacles.LoadTextures();
    obstacles.GenerateObstacles(grid);
}

void Game::Run()
{
    float deltaTime = 0.0f;

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        Update(deltaTime);

        Game::Draw();
    }
}

void Game::Update(float deltaTime)
{
    enemy_spawner.Update(deltaTime, grid);
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    grid.DrawGrid();
    spire.Draw();
    enemy_spawner.DrawSpawner();
    enemy_spawner.DrawEnemies();
    obstacles.DrawObstacles();

    EndDrawing();
}

void Game::Shutdown()
{
    CloseWindow();
}
