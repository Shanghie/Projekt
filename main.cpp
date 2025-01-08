#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void clearScreen() {
    system("cls");
}

int main() {
    Player player1, player2;

    cout << "Gracz 1, ustaw swoje statki." << endl;
    player1.placeShips();
    clearScreen();

    cout << "Gracz 2, ustaw swoje statki." << endl;
    player2.placeShips();
    clearScreen();

    int x, y;
    bool player1Turn = true;
    while (true) {
        bool validShot;
        do {
            cout << (player1Turn ? "\nGracz 1" : "\nGracz 2") << ", wybierz pole do ataku (x y): ";
            cin >> x >> y;

            validShot = player1Turn ? player1.attack(player2, x, y) : player2.attack(player1, x, y);

            if (player1Turn) {
                cout << "\nPlansza Gracza 1 (Twoja):" << endl;
                player1.displayBoard(true);
                cout << "\nPlansza Gracza 2 (Trafienia/Pudła):" << endl;
                player2.displayBoard(false);
            } else {
                cout << "\nPlansza Gracza 2 (Twoja):" << endl;
                player2.displayBoard(true);
                cout << "\nPlansza Gracza 1 (Trafienia/Pudła):" << endl;
                player1.displayBoard(false);
            }

            if (player1Turn && player2.hasLost()) {
                cout << "Gracz 1 wygral!" << endl;
                return 0;
            } else if (!player1Turn && player1.hasLost()) {
                cout << "Gracz 2 wygral!" << endl;
                return 0;
            }

        } while (validShot);

        cout << "\nNacisnij Enter, aby przekazac ture przeciwnikowi...";
        cin.ignore();
        cin.get();
        clearScreen();

        player1Turn = !player1Turn;
    }

    return 0;
}
