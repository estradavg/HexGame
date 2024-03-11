#include "MonteCarlo.h"

// Sets level for AI
void MonteCarlo::setLevel(int level)
{
	simGames = level;
}

// Returns the best move as integer on the board
int MonteCarlo::getBestMove() 
{
    srand(time(NULL));

    int bestResult = 0;
    int bestMove = 0;

    for (int i = 1; i <= HB->getSize(); i++) 
    {
        if (isBlankMove(i)) 
        {
            int currentResult = simulateMoveAndGetWins(i);
            
            if (currentResult > bestResult) 
            {
                bestResult = currentResult;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

bool MonteCarlo::isBlankMove(int move) {
    State S = HB->getState();
    return (S.getColor(move) == State::Player::BLANK);
}

int MonteCarlo::simulateMoveAndGetWins(int move) {
    State S = HB->getState();
    S.setColor(move, HB->Computer);
    return numberOfWins(S);
}

// Returns the number of games won from a given state
int MonteCarlo::numberOfWins(State S) 
{
    int result = 0;
    S.fillMoves();

    for (int i = 0; i < simGames; i++) 
    {
        result += simulateGame(S, HB->Human);
    }
    return result;
}

// Simulates 'simGames' on a given state, and return if has won on that given state
int MonteCarlo::simulateGame(State S, State::Player startingPlayer) 
{
    S.shuffleMoves();

    while (!S.movesEmpty()) 
    {
        int randomMove = S.getNextMove();
        S.setColor(randomMove, startingPlayer);
        startingPlayer = (startingPlayer == HB->Human ? HB->Computer : HB->Human);
    }

    return (HB->hasWon(S) ==  HB->Computer) ? 1 : 0;
}
