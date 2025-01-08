#include "Player.h"

void Player::placeShips(){
 cout << "Plansza gry: \n";
 board.display(true);
 
 
    vector<Ship> ships = {
        {"Jednomasztowiec", 1}, {"Jednomasztowiec", 1}, {"Jednomasztowiec", 1}, {"Jednomasztowiec", 1},
        {"Dwumasztowiec", 2}, {"Dwumasztowiec", 2}, {"Dwumasztowiec", 2},
        {"Trzymasztowiec", 3}, {"Trzymasztowiec", 3},
        {"Czteromasztowiec", 4}
    };

    for (const auto& ship : ships) {
        int x, y;
        char orientation;
        bool placed = false;

        while (!placed) {
            cout << "Umiesc statek " << ship.name << " (rozmiar " << ship.size << ").\n";
            if (ship.size == 1) {
               
                cout << "Podaj wspolrzedne (x y): ";
                string input;
                getline(cin, input);
                stringstream ss(input);

                if (ss >> x >> y) {
                    placed = board.placeShip(x, y, ship, true); 
                    if (!placed) {
                        cout << "Nie można ustawic statku w tej pozycji. Sprobuj ponownie.\n";
                    } else {
                        cout << "Aktualna plansza po umieszczeniu statku:\n";
                        board.display(true);
                    }
                } else {
                    cout << "Niepoprawne dane wejsciowe. Sprobuj ponownie.\n";
                }
            } else {
               
                cout << "Podaj wspolrzedne (x y) i orientację (h - poziomo, v - pionowo): ";
                string input;
                getline(cin, input);
                stringstream ss(input);

                if (ss >> x >> y >> orientation && (orientation == 'h' || orientation == 'v')) {
                    bool horizontal = (orientation == 'h');
                    placed = board.placeShip(x, y, ship, horizontal);
                    if (!placed) {
                        cout << "Nie można ustawic statku w tej pozycji. Sprobuj ponownie.\n";
                    } else {
                        cout << "Aktualna plansza po umieszczeniu statku:\n";
                        board.display(true);
                    }
                } else {
                    cout << "Niepoprawne dane wejściowe. Sprobuj ponownie.\n";
                }
            }
        }
    }
}

void Player::displayBoard(bool showShips) const {
    board.display(showShips);
}

bool Player::attack(Player &opponent, int x, int y) {
    return opponent.board.shoot(x, y);
}

bool Player::hasLost() const {
    return board.allShipsSunk();
}
