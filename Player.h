#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>
#include <sstream>

class Player {
private:
    Board board;

public:
    void placeShips();
    void displayBoard(bool showShips = false) const;
    bool attack(Player &opponent, int x, int y);
    bool hasLost() const;
};

#endif // PLAYER_H
