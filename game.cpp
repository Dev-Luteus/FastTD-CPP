#include "raylib.h"
#include "game.h"

Game::Game() = default;

void Game::Initialize()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FastTD");
    SetTargetFPS(60);

    camera = GameCamera(
        Grid::GetWidth(), Grid::GetHeight(),
        Grid::GetVisibleWidth(), Grid::GetVisibleHeight(),
        Cell::CELL_SIZE);

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
    mouseHandler = new HandleMouse(grid, enemySpawner, wall, spire, camera);
    camera.SetPosition(spire.GetCenterX() * Cell::CELL_SIZE, spire.GetCenterY() * Cell::CELL_SIZE);
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
    camera.Update(deltaTime);
    enemySpawner.Update(deltaTime, grid, spire);
    mouseHandler->UpdateMouse();
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    camera.BeginMode();

    grid.DrawGrid();
    spire.Draw();
    enemySpawner.DrawSpawner();
    enemySpawner.DrawEnemies();
    obstacles.DrawObstacles();
    wall.DrawWalls();

    camera.EndMode();

    DrawUI(); // unrelated to camera
    EndDrawing();
}

void Game::DrawUI()
{
    int uiWidth = SCREEN_WIDTH - (Grid::GetVisibleWidth() * Cell::CELL_SIZE);

    DrawRectangle(SCREEN_WIDTH - uiWidth, 0, uiWidth, SCREEN_HEIGHT, LIGHTGRAY);
    DrawText("Game UI", SCREEN_WIDTH - uiWidth + 10, 10, 26, BLACK);

    DrawText("Move Camera:", SCREEN_WIDTH - uiWidth + 10, 100, 26, BLACK);
    DrawText("WASD", SCREEN_WIDTH - uiWidth + 10, 130, 26, BLACK);

    DrawText("Place Wall:", SCREEN_WIDTH - uiWidth + 10, 200, 26, BLACK);
    DrawText("Left Click", SCREEN_WIDTH - uiWidth + 10, 230, 26, BLACK);
}

void Game::Shutdown()
{
    delete mouseHandler;
    mouseHandler = nullptr;

    CloseWindow();
}
