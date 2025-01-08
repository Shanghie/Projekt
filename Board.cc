#include "Board.h"

Board::Board() : grid(BOARD_SIZE, vector<CellState>(BOARD_SIZE, EMPTY)) {} 

bool Board::isValidPosition(int x, int y) const { // Check if a position is within the board
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool Board::canPlaceShip(int x, int y, int size, bool horizontal) const { // returns true if ship can be placed at position (x, y) with size 'size' 
    int dx = horizontal ? 0 : 1;
    int dy = horizontal ? 1 : 0;

    for (int i = 0; i < size; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;

        if (!isValidPosition(nx, ny) || grid[nx][ny] != EMPTY)
            return false;

        for (int xx = nx - 1; xx <= nx + 1; xx++) {
            for (int yy = ny - 1; yy <= ny + 1; yy++) {
                if (isValidPosition(xx, yy) && grid[xx][yy] == SHIP) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::placeShip(int x, int y, const Ship &ship, bool horizontal) { // places ship at position (x, y) with orientation 'horizontal' or 'vertical'
    if (!canPlaceShip(x, y, ship.size, horizontal)) {
        return false;
    }

    int dx = horizontal ? 0 : 1;
    int dy = horizontal ? 1 : 0;
    Ship newShip = ship;

    for (int i = 0; i < ship.size; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        grid[nx][ny] = SHIP;
        newShip.addPosition(nx, ny);
    }

    ships.push_back(newShip);
    return true;
}

bool Board::shoot(int x, int y) { // returns true if shot hits a ship, false otherwise
    if (!isValidPosition(x, y)) {
        cout << "Nieprawidlowe wspolrzedne. Sprobuj ponownie." << endl;
        return false;
    }

    if (grid[x][y] == HIT || grid[x][y] == MISS) {
        cout << "Już strzelales w to miejsce. Wybierz inne pole." << endl;
        return false;
    }

    if (grid[x][y] == SHIP) {
        grid[x][y] = HIT;
        for (auto& ship : ships) {
            for (auto& pos : ship.positions) {
                if (pos.first == x && pos.second == y) {
                    ship.hits++;
                    if (ship.isSunk()) {
                        cout << "Trafiony, zatopiony! (" << ship.name << ")" << endl;
                    } else {
                        cout << "Trafiony!" << endl;
                    }
                    return true;
                }
            }
        }
    } else {
        grid[x][y] = MISS;
        cout << "Pudlo!" << endl;
        return false;
    }
    return false;
}

bool Board::allShipsSunk() const {
    for (const auto& ship : ships) {
        if (!ship.isSunk()) {
            return false;
        }
    }
    return true;
}

void Board::display(bool showShips) const {
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) cout << i << " ";
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (grid[i][j] == HIT)
                cout << "X ";
            else if (grid[i][j] == MISS)
                cout << "O ";
            else if (showShips && grid[i][j] == SHIP)
                cout << "S ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}
