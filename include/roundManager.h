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
    int enemiesForCurrentRound { 0 };
    int enemiesSpawned { 0 };

public:
    RoundManager() : roundCounter(0), currentState(BUILDING), enemiesForCurrentRound(0), enemiesSpawned(0) {}

    void StartNewRound()
    {
        roundCounter++;
        currentState = DEFENDING;
        enemiesForCurrentRound = 10 + (roundCounter - 1) * 4; // +4 per round
        enemiesSpawned = 0;
    }

    void EndRound()
    {
        currentState = BUILDING;
    }

    [[nodiscard]] bool CanSpawnEnemy() const
    {
        return (currentState == DEFENDING && enemiesSpawned < enemiesForCurrentRound);
    }

    void EnemySpawned()
    {
        enemiesSpawned++;
    }

    [[nodiscard]] bool AllEnemiesSpawned() const
    {
        return enemiesSpawned >= enemiesForCurrentRound;
    }

    void SetRound(int round) { roundCounter = round; }
    void ResetRound() { roundCounter = 0; }
    void SetRoundState(RoundState state) { currentState = state; }

    [[nodiscard]] RoundState GetRoundState() const { return currentState; }
    [[nodiscard]] int GetRound() const { return roundCounter; }
    [[nodiscard]] int GetEnemiesForCurrentRound() const { return enemiesForCurrentRound; }
    [[nodiscard]] int GetEnemiesSpawned() const { return enemiesSpawned; }
};

#endif //ROUNDMANAGER_H