#include "HexBoard.h"
#include "MonteCarlo.h"


HexBoard::HexBoard() {
    initializeBoard();
    S = State();
    G.setEdgeList();
    Human = State::Player::BLACK;
    Computer = State::Player::WHITE;
}

HexBoard::HexBoard(int s, int p, int l) : size(s), player(p), level(l) {
    initializeBoard();
    S = State(s);
    G.setEdgeList();
    Human = (p == 1) ? State::Player::BLACK : State::Player::WHITE;
    Computer = (p == 1) ? State::Player::WHITE : State::Player::BLACK;
}

void HexBoard::initializeBoard() {
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (getCol(j) != size) {
                G.addEdge(getNode(i, j), getNode(i, j + 1)); // Left -> Right
            }
            if (i != size) {
                G.addEdge(getNode(i, j), getNode(i + 1, j)); // Up -> Down
                if (getCol(j) != 1) {
                    G.addEdge(getNode(i, j), getNode(i + 1, j - 1)); // Up -> Left Down
                }
            }
        }
    }

    // Print board helper
    line = "\\";
    for(int i = 1; i < size; i++)
        line += " / \\";
}

void HexBoard::printBoard() 
{
    // Print top
    std::cout << "  1";
    for (int i = 2; i <= size; i++) 
    {
        std::cout << " w " << i;
    }

    // Print first line
    std::cout << "\n1 "; printColor(1);
    for (int i = 2; i < size; i++) 
    {
        std::cout << "---"; printColor(i);
    }

    std::string indent = "";
    for (int i = size; i <= (size * size); i++) 
    {
        if (getCol(i) == size && getRow(i) != size) 
        {
            // Print last node of row
            std::cout << "---"; printColor(i);

            // Print separation line
            indent += ' ';
            std::cout << "\n" << indent << "b " << line << "\n";
            continue;
        }
        if (getCol(i) == 1 && getRow(i) <= size) 
        {
            // Print first node of row
            indent += ' ';
            std::cout << indent << getRow(i) << ' '; printColor(i);
            continue;
        }
        std::cout << "---"; printColor(i);
    }
    std::cout << "\n_________________________________________________________" << "\n";
}

void HexBoard::printColor(int node) 
{
    switch (S.getColor(node)) 
    {
        case State::Player::BLANK:
            std::cout << "+";
            break;
        case State::Player::BLACK:
            std::cout << "B";
            break;
        case State::Player::WHITE:
            std::cout << "W";
            break;
    }
}

void HexBoard::placeMove(int x, int y) 
{
    int node = getNode(x, y);
    if (node > (size * size) || node < 1) 
        throw 1;
    if (S.getColor(node) != State::Player::BLANK) 
        throw 2;

    S.setColor(getNode(x, y), Human);
}

void HexBoard::playComputer() 
{
    MonteCarlo MC(this);
    MC.setLevel(level * 100);
    int move = MC.getBestMove();
    S.setColor(move, Computer);
}

// Returns the hexboard size
int HexBoard::getSize()
{
    return size * size;
}

// Resets the board to a blank state
void HexBoard::reset() 
{
    for (int i = 1; i <= (size * size); i++)
    {
        S.setColor(i, State::Player::BLANK);
    }
    S.setTurns(0);
}

// Returns the current board state
State HexBoard::getState() 
{
    return S;
}

// Overload hasWon() to return the current board state
State::Player HexBoard::hasWon() 
{
    return hasWon(S);
}

// Returns the winner of a given state
State::Player HexBoard::hasWon(State &state)
{
    if (state.getTurns() < size * 2)
    {
        return State::Player::BLANK;
    }

    std::vector<bool> visited((size * size) + 1, false);

    // Helper function to check for a winner for a specific player type
    auto checkPlayerWinner = [&](State::Player player) -> State::Player {
        int start, end, step;

        if (player == State::Player::BLACK)
        {
            start = 1;
            end = size;
            step = 1;
        }
        else // Player::WHITE
        {
            start = 1;
            end = (size * size) - (size - 1);
            step = (player == State::Player::WHITE) ? size : 1;
        }

        for (int i = start; i <= end; i += step)
        {
            if (state.getColor(i) == player)
            {
                bool win = false;
                checkWon(state, player, i, visited, win);
                if (win)
                {
                    return player;
                }
            }
        }

        return State::Player::BLANK;
    };

    // Check human
    State::Player humanWinner = checkPlayerWinner(Human);
    if (humanWinner != State::Player::BLANK)
    {
        return humanWinner;
    }

    // Check computer
    State::Player computerWinner = checkPlayerWinner(Computer);
    if (computerWinner != State::Player::BLANK)
    {
        return computerWinner;
    }

    return State::Player::BLANK;
}

int HexBoard::getNode(int row, int col) 
{
    return ((size * (row - 1)) + col);
}

int HexBoard::getCol(int x) 
{
    return (x % size == 0 ? size : x % size);
}

int HexBoard::getRow(int x) 
{
    return ((x - 1) / size) + 1;
}

// Returns all neighbours from given node of a player
std::vector<int> HexBoard::getNeighboursOf(int i, State &state, State::Player wanted, std::vector<bool> &visited) 
{
    std::vector<int> edgeVector;
    const std::vector<int>& temp = G.getEdges(i);

    for (std::vector<int>::const_iterator it = temp.begin(); it != temp.end(); ++it) 
    {
        if (state.getColor(*it) == wanted && !visited[*it]) 
        {
            edgeVector.push_back(*it);
        }
    }

    return edgeVector;
}

// Find winner on the current state of a player
void HexBoard::checkWon(State &state, State::Player wanted, int current, std::vector<bool> &visited, bool &won) 
{

    if ((wanted == Computer && (Computer == State::Player::WHITE ? getCol(current) : getRow(current)) == size) ||
    (wanted == Human && (Human == State::Player::BLACK ? getRow(current) : getCol(current)) == size))
    {
        // If the wanted player has won on the state
        won = true;
    }


    if (visited[current]) 
    {
        return;
    }

    visited[current] = true;
    std::vector<int> neighbours = getNeighboursOf(current, state, wanted, visited);

    if (!neighbours.empty()) 
    {
        for (std::vector<int>::iterator j = neighbours.begin(); j != neighbours.end(); j++) 
        {
            checkWon(state, wanted, *j, visited, won);
        }
    } 
    else 
    {
        return;
    }
}
