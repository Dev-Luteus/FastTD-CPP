#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>

class GameCamera
{
private:
    Camera2D camera { 0 };
    static constexpr float CAMERA_MOVE_SPEED { 700.0f };

    float minX { 0 };
    float minY { 0 };
    float maxX { 0 };
    float maxY { 0 };

    int gridWidth { 0 };
    int gridHeight { 0 };
    int visibleWidth { 0 };
    int visibleHeight { 0 };

    int cellSize { 0 }; // pixels

public:
    GameCamera() = default; // We set the values in Game.Initialize()
    GameCamera(int gridWidth, int gridHeight, int visibleWidth, int visibleHeight, int cellSize);

    void Update(float deltaTime);
    void BeginMode() const;
    void EndMode() const;

    [[nodiscard]] Camera2D GetCamera() const { return camera; }
    [[nodiscard]] Vector2 GetPosition() const { return camera.target; }

    void SetPosition(float x, float y);
};

#endif //CAMERA_H
