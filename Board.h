#ifndef BOARD_H
#define BOARD_H

#include "CellState.h"
#include "Ship.h"
#include <vector>
#include <iostream>
using namespace std;

const int BOARD_SIZE = 10;

class Board {
private:
    vector<vector<CellState>> grid;
    vector<Ship> ships;

public:
    Board();
    bool isValidPosition(int x, int y) const;
    bool canPlaceShip(int x, int y, int size, bool horizontal) const;
    bool placeShip(int x, int y, const Ship &ship, bool horizontal);
    bool shoot(int x, int y);
    bool allShipsSunk() const;
    void display(bool showShips) const;
};

#endif // BOARD_H
