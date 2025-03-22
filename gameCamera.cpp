#include "gameCamera.h"
#include <raymath.h>

#include "cell.h"

/* Updated this and spend 3 hours only to realize that the problem was not the camera.
 * I thought it was assymetric, since I saw more to the left than I did to the right, because:
 * - The spire is supposed to be in the middle.
 *
 * However, the spire is a 5x5, and my grid width and height was 40
 * I had to correct it to 41..
 */
GameCamera::GameCamera(int gridWidth, int gridHeight, int visibleWidth, int visibleHeight, int cellSize, int uiWidth)
    : gridWidth(gridWidth), gridHeight(gridHeight),
      visibleWidth(visibleWidth), visibleHeight(visibleHeight),
      cellSize(cellSize), uiWidth(uiWidth)
{
    // Basic camera init settings
    camera.target = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    auto gameAreaWidth = static_cast<float>(GetScreenWidth() - uiWidth);
    auto gameAreaHeight = static_cast<float>(GetScreenHeight());

    camera.offset =
    {
        gameAreaWidth / 2.0f,
        gameAreaHeight / 2.0f
    };

    auto totalWidth = static_cast<float>(gridWidth * cellSize);
    auto totalHeight = static_cast<float>(gridHeight * cellSize);

    minX = camera.offset.x;
    maxX = totalWidth - (gameAreaWidth - camera.offset.x);

    minY = camera.offset.y;
    maxY = totalHeight - camera.offset.y;

    SetPosition(totalWidth / 2.0f, totalHeight / 2.0f);
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