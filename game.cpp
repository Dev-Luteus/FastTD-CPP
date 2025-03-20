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

    enemySpawner.LoadTextures();
    enemySpawner.PlaceSpawner(grid);
    enemySpawner.SetTarget(spire.GetCenterX(), spire.GetCenterY());

    obstacles.LoadTextures();
    obstacles.GenerateObstacles(grid);

    wall.LoadTextures();
    mouseHandler = new HandleMouse(grid, enemySpawner, wall, spire);
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
    enemySpawner.Update(deltaTime, grid, spire);
    mouseHandler->UpdateMouse();
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    grid.DrawGrid();
    spire.Draw();
    enemySpawner.DrawSpawner();
    enemySpawner.DrawEnemies();
    obstacles.DrawObstacles();
    wall.DrawWalls();

    EndDrawing();
}

void Game::Shutdown()
{
    delete mouseHandler;
    mouseHandler = nullptr;

    CloseWindow();
}
