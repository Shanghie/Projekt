#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>
#include <utility>
using namespace std;

class Ship {
public:
    string name;
    int size;
    int hits = 0;
    vector<pair<int, int>> positions;

    Ship(string name, int size);
    bool isSunk() const;
    void addPosition(int x, int y);
};

#endif // SHIP_H
