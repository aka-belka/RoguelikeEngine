#include "Monster.h"
#include "Player.h"
#include <iostream>

Monster::Monster(const std::string& id, const std::string& name, int health, int attackPower, int defense, int expReward) {
    this->id = id;
    this->name = name;
    this->maxHealth = health;
    this->health = health;
    this->attackPower = attackPower;
    this->defense = defense;
    this->expReward = expReward;
}

Monster::Monster(const Monster& other) {
    this->id = other.id;
    this->name = other.name;
    this->maxHealth = other.maxHealth;
    this->health = other.maxHealth;
    this->attackPower = other.attackPower;
    this->defense = other.defense;
    this->expReward = other.expReward;
    this->dropItemIds = other.dropItemIds;
}

void Monster::attack(Player* target) {
    int damage = attackPower - target->getDefense();
    if (damage < 1) damage = 1;
    std::cout << name << " attacks! Damage: " << damage << std::endl;
    target->takeDamage(damage);
}

void Monster::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
    std::cout << name << " takes " << amount << " damage. HP: " << health << "/" << maxHealth << std::endl;
}

void Monster::addDropItemId(const std::string& itemId) {
    dropItemIds.push_back(itemId);
}

Monster::~Monster() {}