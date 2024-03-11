#include "Game.h"

/* Default */
Game::Game()
{
    setGame();
    playGame();
}

/* Configure game settings */
void Game::setGame()
{
    std::cout << "Welcome to Hex Game! \n";

    std::cout << "Press (1) to play with default values\nPress (2) to set game values\n> ";
    int gameSelection;
    std::cin >> gameSelection;

    int size, player, level;

    if (gameSelection <= 1 || gameSelection > 2)
    {
        std::cout << "\nContinuing with default settings...\n";
        HB = HexBoard();
        return;
    }
    else
    {
        /* Set Difficult Level */
        std::cout << "Enter Level of difficulty [1-10] (the higher the level, the longer each turn takes to compute).\n";
        std::cin >> level;

        while (level < 1 || level > 10)
        {
            std::cout << "\nInvalid difficult level! Try again ... \n>";
            std::cin >> level;
        }
        
        /* Set Board Size */
        std::cout << "\nInput the desired board size (from 5 - 11): ";
        std::cin >> size;

        while (size < 5 && size > 11)
        {
            std::cout << "\nInvalid size! Try again ... \n>";
            std::cin >> size;
        }
        
        /* Set Player */
        std::cout << "\nPress 1 for Black (B) Player\nPress 2 for White (W) Player\n>";
        std::cin >> player;

        /* Player Black = 0, Player White = 1 */
        while (player < 1 && player > 2)
        {
            std::cout << "\nInvalid player! Try again ... \n>";
            std::cin >> player;
        }

        if (player == 0)
        {
            std::cout << "You are playing as Black, your goal is to connect Top and Bottom of the board\n";
        }
        else
        {
            std::cout << "You are playing as White, your goal is to connect Left and Right sides of the board\n";
        }

        /* Pass configuration to HexBoard class */
        HB = HexBoard(size, player, level);
    }
}

/* Main loop */
void Game::playGame()
{
    char useInput;
    State::Player won;

    /* Print empty board */
    HB.printBoard();

    /* Main */
    while (true)
    {
        won = HB.hasWon();
        if (won == HB.Human) 
        {
            std::cout << "You have won.\nPlay again? (y/n): ";
            std::cin >> useInput;
            if (!restart(useInput)) break;
        } 
        else if (won == HB.Computer) 
        {
            std::cout << "You have lost.\nPlay again? (y/n): ";
            std::cin >> useInput;
            if (!restart(useInput)) break;
        }

        if(!setMove())
        {
            std::cout << "\n - - - Thank you for playing HexGame! - - - \n";
            break;
        }
    }
}

inline bool Game::restart(char userInput) 
{
    char lowerInput = std::tolower(userInput);
    
    if (lowerInput == 'y') 
    {
        HB.reset();
        HB.printBoard();
        return true;
    } 
    else if (lowerInput == 'n') 
    {
        std::cout << "\n - - - Thank you for playing HexGame! - - - \n";
        return false;
    } 
    else 
    {
        // Invalid input, let the user try again or handle the case accordingly
        return restart(getValidInput());
    }
}

char Game::getValidInput() 
{
    char userInput;
    std::cout << "Invalid input. Please enter 'y' or 'n': ";
    std::cin >> userInput;
    return std::tolower(userInput);
}

/* Set move */
inline bool Game::setMove()
{
    std::cout << "\nInput a valid move coordinate |x, y| (0 to quit): ";
    std::cin >> x;
    if (x == 0) return 0;
    std::cin >> y;

    try
    {
        HB.placeMove(x, y);

        /* Play computer's move */
        std::cout << "Computing next move ...\n";
        HB.playComputer();
        HB.printBoard();
    }
    catch(int e)
    {
        switch (e) 
        {
            case 1:
                std::cout << "Invalid Coordinates! Please try again.\n";
                break;
            case 2:
                std::cout << "A piece has already been placed on those coordinates. Please try again.\n";
                break;
        }
    }
    return 1;
}
