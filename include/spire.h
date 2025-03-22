#ifndef SPIRE_H
#define SPIRE_H

#include <cstdio>
#include "grid.h"
#include <raylib.h>

class Spire
{
private:
    static constexpr int SPIRE_SIZE { 5 }; // 5x5
    static constexpr int SPIRE_SPRITE_ID { 100 };
    int SPIRE_HEALTH { 100 };

    Texture2D texture;
    int gridX;
    int gridY;

public:

    Spire() = default;
    ~Spire();

    void LoadTextures();
    void PlaceInCenter(Grid& grid);
    void Draw() const;

    [[nodiscard]] int GetCenterX() const;
    [[nodiscard]] int GetCenterY() const;
    [[nodiscard]] int GetHealth() const { return SPIRE_HEALTH; }

    [[nodiscard]] int GetSpireId() { return SPIRE_SPRITE_ID; }

    void ModifyHealth(int damage)
    {
        SPIRE_HEALTH -= damage;
        printf("Spire new health: %d\n", SPIRE_HEALTH);
    }
};

#endif //SPIRE_H