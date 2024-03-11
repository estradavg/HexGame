#include "State.h"

State::State() : turns(0) {
    initializePiece();
}

State::State(int s) : size(s), turns(0) {
    initializePiece();
}

void State::initializePiece() {
    piece.resize(size * size);
}


// Sets the colour of a given vertex
void State::setColor(int vertex, Player c) 
{
    piece[vertex] = c;
    turns++;
}

// Gets the colour of a given vertex
State::Player State::getColor(int vertex) 
{
    return piece[vertex];
}

// Sets the number of turns played
void State::setTurns(int turns) 
{
    this->turns = turns;
}

// Gets the number of turns played
int State::getTurns() 
{
    return turns;
}

// Returns the next move
int State::getNextMove() 
{
    int move = moves.back();
    moves.pop_back();
    return move;
}

// Fills the moves vector with all possible moves
void State::fillMoves() 
{
    for (int i = 1; i <= (size * size); i++) 
    {
        if (getColor(i) == Player::BLANK) 
        {
            moves.push_back(i);
        }
    }
}

// Shuffles the moves vector
void State::shuffleMoves() 
{
    std::random_shuffle(moves.begin(), moves.end());
}

// Returns true if there are no more moves left
bool State::movesEmpty() 
{
    return moves.empty();
}