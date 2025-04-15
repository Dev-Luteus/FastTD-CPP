#include "raylib.h"
#include "game.h"
#include <string>
#include "profileScope.h"

Game::Game() = default;

void Game::Initialize()
{
    PROFILE_FUNCTION();

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

    mouseHandler = new HandleMouse(grid, enemySpawner, wall, spire, camera, player,
                              roundManager, SCREEN_WIDTH, UI_WIDTH);

    camera.SetPosition(spire.GetCenterX() * Cell::CELL_SIZE, spire.GetCenterY() * Cell::CELL_SIZE);
}

void Game::Run()
{
    PROFILE_FUNCTION();

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
    PROFILE_FUNCTION();

    {
        PROFILE_GAME("Camera.Update");
        camera.Update(deltaTime);
    }

    {
        PROFILE_ENEMY("EnemySpawner.Update");
        enemySpawner.Update(deltaTime, grid, spire, roundManager);
    }

    {
        PROFILE_GAME("MouseHandler.Update");
        mouseHandler->UpdateMouse();
    }
}

void Game::Draw()
{
    PROFILE_FUNCTION();

    {
        PROFILE_GAME("BeginFrame");
        BeginDrawing();
        ClearBackground(RAYWHITE);
    }

    {
        PROFILE_GAME("WorldBegin");
        camera.BeginMode();

        {
            PROFILE_GRID("Draw");
            grid.DrawGrid();
        }

        {
            PROFILE_GAME("SpireDraw");
            spire.Draw();
        }

        {
            PROFILE_ENEMY("Draw");
            enemySpawner.DrawSpawner();
            enemySpawner.DrawEnemies();
        }

        {
            PROFILE_GAME("ObstacleDraw");
            obstacles.DrawObstacles();
        }

        {
            PROFILE_GAME("WallDraw");
            wall.DrawWalls();
        }

        {
            PROFILE_GAME("WorldEnd");
            camera.EndMode();
        }
    }

    {
        PROFILE_UI("Draw");
        DrawUI();
    }

    {
        PROFILE_GAME("EndFrame");
        EndDrawing();
    }
}

void Game::DrawUI()
{
    PROFILE_FUNCTION();

    DrawUIPanel();
    int currentY = 20;

    DrawUILabel("FAST TD", currentY);
    currentY += 50;

    DrawUICurrency(currentY);
    currentY += 50;

    DrawUIHealth(currentY);
    currentY += 50;

    DrawUIDivider(currentY);
    currentY += 30;

    currentY += 50; // spacing.

    // Controls
    DrawUISection("CONTROLS", currentY);
    currentY += 40;

    DrawUILabel("Move Camera: WASD", currentY);
    currentY += 40;

    DrawUILabel("Place Wall: Left Click", currentY);
    currentY += 50;

    DrawUIDivider(currentY);
    currentY += 20;

    // Round
    std::string roundText = "ROUND: " + std::to_string(roundManager.GetRound());
    DrawUILabel(roundText.c_str(), currentY);
    currentY += 40;

    // State
    const char* stateText = roundManager.GetRoundState() == RoundManager::BUILDING ?
                           "Building Phase" : "Defending Phase";
    DrawUILabel(stateText, currentY);
    currentY += 40;

    // Enemies
    if (roundManager.GetRoundState() == RoundManager::DEFENDING)
    {
        std::string enemyText = "Enemies: " +
                              std::to_string(roundManager.GetEnemiesSpawned()) +
                              " / " +
                              std::to_string(roundManager.GetEnemiesForCurrentRound());

        DrawUILabel(enemyText.c_str(), currentY);
        currentY += 40;
    }

    if (roundManager.GetRoundState() == RoundManager::BUILDING)
    {
        if (DrawUIButton("Start Round", SCREEN_HEIGHT - 100))
        {
            player.StartRound(roundManager);
        }
    }
}

void Game::DrawUIPanel()
{
    DrawRectangle(SCREEN_WIDTH - UI_WIDTH, 0, UI_WIDTH, SCREEN_HEIGHT, DARKGRAY);
}

void Game::DrawUILabel(const char* text, int y)
{
    int textWidth = MeasureText(text, UI_TEXT_SIZE);
    int x = SCREEN_WIDTH - UI_WIDTH + (UI_WIDTH - textWidth) / 2;
    DrawText(text, x, y, UI_TEXT_SIZE, WHITE);
}

void Game::DrawUISection(const char* title, int y)
{
    DrawUILabel(title, y);
}

bool Game::DrawUIButton(const char* text, int y, int height)
{
    int buttonWidth = 200;
    int buttonX = SCREEN_WIDTH - UI_WIDTH + (UI_WIDTH - buttonWidth) / 2;

    Rectangle buttonRect =
    {
        static_cast<float>(buttonX),
        static_cast<float>(y),
        static_cast<float>(buttonWidth),
        static_cast<float>(height)
    };

    Color buttonColor = GRAY;
    bool clicked = false;

    // Mouse
    Vector2 mousePoint = GetMousePosition();
    bool isMouseOverButton = CheckCollisionPointRec(mousePoint, buttonRect);

    if (isMouseOverButton)
    {
        buttonColor = DARKGRAY;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            clicked = true;
        }
    }

    DrawRectangleRec(buttonRect, buttonColor);
    DrawRectangleLines(buttonX, y, buttonWidth, height, BLACK); // border

    // Text in button
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    int textX = buttonX + (buttonWidth - textWidth) / 2;
    int textY = y + (height - fontSize) / 2;

    DrawText(text, textX, textY, fontSize, WHITE);

    return clicked;
}

void Game::DrawUICurrency(int y)
{
    std::string currencyText = "GOLD: " + std::to_string(player.GetCurrency());

    int textWidth = MeasureText(currencyText.c_str(), UI_TEXT_SIZE);
    int x = SCREEN_WIDTH - UI_WIDTH + (UI_WIDTH - textWidth) / 2;

    Rectangle currencyBox =
    {
        static_cast<float>(x - 10),
        static_cast<float>(y - 5),
        static_cast<float>(textWidth + 20),
        static_cast<float>(UI_TEXT_SIZE + 10)
    };

    DrawRectangleRec(currencyBox, GOLD);
    DrawRectangleLinesEx(currencyBox, 2, BLACK);
    DrawText(currencyText.c_str(), x, y, UI_TEXT_SIZE, BLACK);
}

void Game::DrawUIDivider(int y)
{
    int lineWidth = UI_WIDTH - (UI_MARGIN * 2);
    int x = SCREEN_WIDTH - UI_WIDTH + UI_MARGIN;

    DrawLine(x, y, x + lineWidth, y, WHITE);
}

void Game::DrawUIHealth(int y)
{
    std::string healthText = "SPIRE HP: " + std::to_string(spire.GetHealth());

    int textWidth = MeasureText(healthText.c_str(), UI_TEXT_SIZE);
    int x = SCREEN_WIDTH - UI_WIDTH + (UI_WIDTH - textWidth) / 2;

    Rectangle healthBox =
    {
        static_cast<float>(x - 10),
        static_cast<float>(y - 5),
        static_cast<float>(textWidth + 20),
        static_cast<float>(UI_TEXT_SIZE + 10)
    };

    DrawRectangleRec(healthBox, LIGHTGRAY);
    DrawRectangleLinesEx(healthBox, 1, BLACK);
    DrawText(healthText.c_str(), x, y, UI_TEXT_SIZE, BLACK);
}

void Game::Shutdown()
{
    PROFILE_FUNCTION();

    delete mouseHandler;
    mouseHandler = nullptr;

    CloseWindow();
}
