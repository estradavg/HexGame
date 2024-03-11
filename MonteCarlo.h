#ifndef MONTECARLO_H
#define MONTECARLO_H
#include "HexBoard.h"

class MonteCarlo 
{
public:
    MonteCarlo(HexBoard *HB) : HB(HB) {};
    int getBestMove();
    void setLevel(int level);

private:
    bool isBlankMove(int move);
    int simulateMoveAndGetWins(int move);
    int simulateGame(State S, State::Player player);
    int numberOfWins(State S);
    int simGames;
    HexBoard *HB;
};

#endif /* MONTECARLO_H */
