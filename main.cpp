#include <iostream>
#include <raylib.h>

int main()
{
    constexpr int screenWidth = { 1920 };
    constexpr int screenHeight = { 1080 };

    SetTargetFPS(200);
    InitWindow(screenHeight, screenWidth, "FastTD");

    while (!WindowShouldClose())
    {

    }

    return 0;
}