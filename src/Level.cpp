#include "Level.h"
#include <iostream>

Level::Level(int size) {
    this->size = size;
    rooms.resize(size, std::vector<Room*>(size, nullptr));
}

void Level::generate() {
    std::cout << "Generating level " << size << "x" << size << "..." << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            rooms[i][j] = new Room("normal");
        }
    }
    std::cout << "Level generated successfully!" << std::endl;
}

Room* Level::getRoom(int x, int y) {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return rooms[x][y];
    }
    return nullptr;
}

void Level::printLevel() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << "[ ] ";
        }
        std::cout << std::endl;
    }
}