#ifndef ROUNDMANAGER_H
#define ROUNDMANAGER_H

class RoundManager
{
public:
    enum RoundState
    {
        BUILDING,
        DEFENDING
    };

private:
    int roundCounter { 0 };
    RoundState currentState { BUILDING };

public:
    void SetRound(int round) { roundCounter = round; }
    void ResetRound() { roundCounter = 0; }
    void SetRoundState(RoundState state) { currentState = state; }

    [[nodiscard]] RoundState GetRoundState() const { return currentState; }
    [[nodiscard]] int GetRound() const { return roundCounter; }
};

#endif //ROUNDMANAGER_H
