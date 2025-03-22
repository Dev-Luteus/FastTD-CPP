#ifndef PLAYER_H
#define PLAYER_H

#include "roundManager.h"

class Player
{
private:
    int currency { 100 };

public:
    Player() = default;

    [[nodiscard]] int GetCurrency() const { return currency; }
    void SetCurrency(int amount) { currency += amount; }

    void StartRound(RoundManager& roundManager)
    {
        if (roundManager.GetRoundState() == RoundManager::BUILDING)
        {
            roundManager.StartNewRound();
        }
    }
};

#endif //PLAYER_H
