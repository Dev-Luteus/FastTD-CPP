#ifndef SPIRE_H
#define SPIRE_H

#include "grid.h"
#include <raylib.h>

class Spire
{
    private:
    static constexpr int SPIRE_SIZE { 5 }; // 5x5
    static constexpr int SPIRE_SPRITE_ID { 100 };

    Texture2D texture;
    int gridX;
    int gridY;

    public:
    Spire() = default;
    ~Spire();

    void LoadTextures();
    void PlaceInCenter(Grid& grid);
    void Draw() const;
};

#endif //SPIRE_H