#ifndef GAME_H
#define GAME_H

class Game
{
    private:
    static constexpr int screenWidth { 1920 };
    static constexpr int screenHeight { 1080 };

    void draw();

    public:
    Game() = default; // Default Constructor no args ( if no args = use default )

    void initialize();
    void run();
    void shutdown();
};

#endif //GAME_H
