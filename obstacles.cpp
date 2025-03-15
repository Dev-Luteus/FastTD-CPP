#include "obstacles.h"
#include <string>

void Obstacles::LoadTextures()
{
    for (int i = 0; i < MAX_OBSTACLES_TEXTURES; ++i)
    {
        std::string fileName = "resources/path_tiles/" + std::to_string(i+1) + ".png";

        obstacleTextures[i] = LoadTexture(fileName.c_str());
    }
}

void Obstacles::GenerateObstacles()
{

}

void Obstacles::DrawObstacles()
{

}
