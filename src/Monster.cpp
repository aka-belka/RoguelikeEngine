#include "Player.h"
#include "Monster.h"
#include <iostream>

Monster::Monster(std::string id, std::string name, int health, int attackPower, int defense) {
    this->id = id;
    this->name = name;
    this->health = health;
    this->attackPower = attackPower;
    this->defense = defense;
}

void Monster::attack(Player* target) {
    std::cout << name << " attacks! Damage: " << attackPower << std::endl;
    target->takeDamage(attackPower);
}

void Monster::takeDamage(int amount) {
    health -= amount;
    std::cout << name << " takes " << amount << " damage. HP: " << health << std::endl;
    if (health <= 0) {
        dropLoot();
    }
}

void Monster::dropLoot() {
    std::cout << name << " dies and drops loot!" << std::endl;
}

std::string Monster::getName() {
    return name;
}