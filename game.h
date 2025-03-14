﻿#ifndef GAME_H
#define GAME_H
#include "grid.h"

class Game
{
    private:
    static constexpr int SCREEN_WIDTH { 1920 };
    static constexpr int SCREEN_HEIGHT { 1080 };

    Grid grid;

    void Draw();

    public:
    Game() = default; // Default Constructor no args ( if no args = use default )

    void Initialize();
    void Run();
    void Shutdown();
};

#endif //GAME_H
