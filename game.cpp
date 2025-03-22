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
        Cell::CELL_SIZE, UI_WIDTH);

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
    roundManager.SetRoundState(RoundManager::BUILDING);

    mouseHandler = new HandleMouse(grid, enemySpawner, wall, spire, camera, player, roundManager);
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
    enemySpawner.Update(deltaTime, grid, spire, roundManager);
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
    int buttonWidth = 200;
    int buttonHeight = 50;
    int buttonX = SCREEN_WIDTH - UI_WIDTH + (UI_WIDTH - buttonWidth) / 2;
    int buttonY = 300;

    DrawRectangle(SCREEN_WIDTH - UI_WIDTH, 0, UI_WIDTH, SCREEN_HEIGHT, LIGHTGRAY);
    DrawText("Game UI", SCREEN_WIDTH - UI_WIDTH + 10, 10, 26, BLACK);

    DrawText("Move Camera:", SCREEN_WIDTH - UI_WIDTH + 10, 100, 26, BLACK);
    DrawText("WASD", SCREEN_WIDTH - UI_WIDTH + 10, 130, 26, BLACK);

    DrawText("Place Wall:", SCREEN_WIDTH - UI_WIDTH + 10, 200, 26, BLACK);
    DrawText("Left Click", SCREEN_WIDTH - UI_WIDTH + 10, 230, 26, BLACK);

    const char* stateText = roundManager.GetRoundState() == RoundManager::BUILDING ?
                           "Building Phase" : "Defending Phase";

    DrawText(stateText, SCREEN_WIDTH - UI_WIDTH + 10, 270, 26, BLACK);

    // Draw Button
    Rectangle startRoundButton =
    {
        (float)buttonX,
        (float)buttonY,
        (float)buttonWidth,
        (float)buttonHeight
    };

    auto buttonColour = GRAY;

    Vector2 mousePoint = GetMousePosition();
    bool isMouseOverButton = CheckCollisionPointRec(mousePoint, startRoundButton);

    if (isMouseOverButton)
    {
        buttonColour = DARKGRAY;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            player.StartRound(roundManager);
        }
    }

    DrawRectangleRec(startRoundButton, buttonColour);
    DrawText("Start Round", buttonX + 20, buttonY + 15, 20, WHITE);
}

void Game::Shutdown()
{
    delete mouseHandler;
    mouseHandler = nullptr;

    CloseWindow();
}
