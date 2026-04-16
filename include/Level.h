#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Room.h"

class Level {
private:
    int size;
    std::vector<std::vector<Room*>> rooms;

public:
    Level(int size);
    void generate();
    Room* getRoom(int x, int y);
    void printLevel();
};

#endif