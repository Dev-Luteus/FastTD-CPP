#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "obstacles.h"
#include "spire.h"
#include "enemySpawner.h"
#include "gameCamera.h"
#include "handleMouse.h"
#include "roundManager.h"
#include "wall.h"

class Game
{
// this private: accessor is unnecessary, but I will include it in every file
private:
    static constexpr int SCREEN_WIDTH { 1920 };
    static constexpr int SCREEN_HEIGHT { 1080 };
    static constexpr int UI_WIDTH { SCREEN_WIDTH / 6 };
    static constexpr int UI_MARGIN { 10 };
    static constexpr int UI_TEXT_SIZE { 26 };

    Grid grid;
    Spire spire;
    Obstacles obstacles;
    EnemySpawner enemySpawner;
    Wall wall;
    HandleMouse* mouseHandler { nullptr };
    GameCamera camera;
    RoundManager roundManager;
    Player player;

    void Draw();
    void Update(float deltaTime);
    void DrawUI();

    // TODO: Refactor into its own class
    // UI helpers
    void DrawUIPanel();
    void DrawUILabel(const char* text, int y);
    void DrawUISection(const char* title, int y);
    bool DrawUIButton(const char* text, int y, int height = 50);
    void DrawUICurrency(int y);
    void DrawUIDivider(int y);
    void DrawUIHealth(int y);

public:
    Game();

    void Initialize();
    void Run();
    void Shutdown();

    [[nodiscard]] int GetScreenWidth() const { return SCREEN_WIDTH; }
    [[nodiscard]] int GetScreenHeight() const { return SCREEN_HEIGHT; }
    [[nodiscard]] int GetUIWidth() const { return UI_WIDTH; }
};

#endif //GAME_H
