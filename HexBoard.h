#ifndef HEXBOARD_H
#define	HEXBOARD_H
#include "State.h"
#include "Graph.h"
#include <iostream>
#include <string>

class HexBoard
{
public:
    HexBoard();
    HexBoard(int s, int p, int l);

    void initializeBoard();
    void printBoard();
    void printColor(int node);

    void placeMove(int x, int y);
    void playComputer();
    int getSize();
    void reset();

    State getState();
    State::Player hasWon();
    State::Player hasWon(State &state);

    State::Player Human;
    State::Player Computer;
private:
    int size = 11;
    int player = 1; 
    int level = 10;
    std::string line;

    State S;
    Graph G;

    inline int getNode(int row, int col);
    inline int getCol(int x);
    inline int getRow(int x);

    void switchPlayer();
    std::vector<int> getNeighboursOf(int i, State &state, State::Player wanted, std::vector<bool> &visited);
    void checkWon(State &state, State::Player wanted, int current, std::vector<bool> &visited, bool &won);
};

#endif	/* HEXBOARD_H */