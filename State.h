#ifndef STATE_H
#define	STATE_H
#include <vector>
#include <algorithm>

class State {
public:

    State();
    State(int size);
    enum class Player { BLANK = 0, BLACK = 1, WHITE = 2 };


    void initializePiece();
    Player getColor(int vertex);
    void setColor(int vertex, Player c);

    void setTurns(int turns);
    int getTurns();

    void fillMoves();
    bool movesEmpty();
    void shuffleMoves();
    int getNextMove();

private:
    int size = 11;
    int turns;
    std::vector<Player> piece;
    std::vector<int> moves;
};

#endif	/* STATE_H */

