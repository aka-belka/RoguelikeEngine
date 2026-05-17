#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Room.h"

class ModLoader;

class Level {
private:
    int width;
    int height;
    std::vector<std::vector<Room*>> rooms;
    int enemiesRemaining;

public:
    Level(int width, int height);
    void generate(ModLoader* modLoader);
    Room* getRoom(int x, int y);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getEnemiesRemaining() const { return enemiesRemaining; }
    void enemyDefeated();
    ~Level();
};

#endif