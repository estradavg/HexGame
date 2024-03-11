#ifndef GAME_H
#define	GAME_H
#include "HexBoard.h"
#include <iostream>

class Game
{
public:
    Game();

    void setGame();
    void playGame();
    inline bool restart(char r);
    char getValidInput(); 
    inline bool setMove();

private:
    HexBoard HB;
    int x, y;
};

#endif	/* GAME_H */
