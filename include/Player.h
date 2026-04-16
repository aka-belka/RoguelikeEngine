#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Item.h"

class Player {
private:
    int health;
    std::vector<Item*> inventory;
    int x, y; 

public:
    Player();
    void move(char direction);
    void attack(class Monster* target);
    void pickUp(Item* item);
    void useItem(int index);
    void takeDamage(int amount);
    int getHealth();
};

#endif