#include "Ship.h"

Ship::Ship(string name, int size) : name(name), size(size) {}

bool Ship::isSunk() const {
    return hits == size;
}

void Ship::addPosition(int x, int y) {
    positions.push_back({x, y});
}
