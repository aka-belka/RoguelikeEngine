#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>
#include "Item.h"


class Monster {
private:
    std::string id;
    std::string name;
    int health;
    int attackPower;
    int defense;
    std::vector<Item*> dropItems;

public:
    Monster(std::string id, std::string name, int health, int attackPower, int defense);
    void attack(class Player* target);
    void takeDamage(int amount);
    void dropLoot();
    std::string getName();
};

#endif