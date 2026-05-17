#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Item.h"

class Monster;

class Player {
private:
    int maxHealth;
    int health;
    int level;
    int experience;
    int attackPower;
    int defense;
    std::vector<Item*> inventory;
    int x, y;

public:
    Player();
    ~Player();
    
    void attack(Monster* target);
    void takeDamage(int amount);
    void heal(int amount);
    void gainExp(int amount);
    void levelUp();
    void pickUp(Item* item);
    void useItem(int index);
    void setPosition(int newX, int newY);
    
    int getX() const { return x; }
    int getY() const { return y; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    int getAttackPower() const { return attackPower; }
    int getDefense() const { return defense; }
    std::vector<Item*>& getInventory() { return inventory; }
    bool isAlive() const { return health > 0; }
};

#endif