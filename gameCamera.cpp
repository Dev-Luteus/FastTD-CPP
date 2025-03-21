#include "gameCamera.h"
#include <raymath.h>

GameCamera::GameCamera(int gridWidth, int gridHeight, int visibleWidth, int visibleHeight, int cellSize)
    : gridWidth(gridWidth), gridHeight(gridHeight),
      visibleWidth(visibleWidth), visibleHeight(visibleHeight),
      cellSize(cellSize)
{
    // Basic camera init settings
    camera.target = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Center!
    camera.offset =
    {
        static_cast<float>(visibleWidth * cellSize) / 2.0f,
        static_cast<float>(visibleHeight * cellSize) / 2.0f
    };

    auto visibleWidthPixels = static_cast<float>(visibleWidth * cellSize);
    auto visibleHeightPixels = static_cast<float>(visibleHeight * cellSize);
    auto totalWidthPixels = static_cast<float>(gridWidth * cellSize);
    auto totalHeightPixels = static_cast<float>(gridHeight * cellSize);

    minX = visibleWidthPixels / 2.0f;
    minY = visibleHeightPixels / 2.0f;
    maxX = totalWidthPixels - minX;
    maxY = totalHeightPixels - minY;

    SetPosition(totalWidthPixels / 2.0f, totalHeightPixels / 2.0f);
}

void GameCamera::Update(float deltaTime)
{
    Vector2 position = camera.target;
    bool moved = false;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        position.y -= CAMERA_MOVE_SPEED * deltaTime;
        moved = true;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        position.y += CAMERA_MOVE_SPEED * deltaTime;
        moved = true;
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        position.x -= CAMERA_MOVE_SPEED * deltaTime;
        moved = true;
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        position.x += CAMERA_MOVE_SPEED * deltaTime;
        moved = true;
    }

    if (moved)
    {
        position.x = Clamp(position.x, minX, maxX);
        position.y = Clamp(position.y, minY, maxY);

        camera.target = position;
    }
}

void GameCamera::SetPosition(float x, float y)
{
    x = Clamp(x, minX, maxX);
    y = Clamp(y, minY, maxY);

    camera.target = { x, y };
}

void GameCamera::BeginMode() const
{
    BeginMode2D(camera);
}

void GameCamera::EndMode() const
{
    EndMode2D();
}