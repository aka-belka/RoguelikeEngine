#include "Player.h"
#include "Monster.h"
#include <iostream>

Player::Player() {
    maxHealth = 100;
    health = 100;
    level = 1;
    experience = 0;
    attackPower = 15;
    defense = 5;
    x = 0;
    y = 0;
}

void Player::attack(Monster* target) {
    int damage = attackPower - target->getDefense();
    if (damage < 1) damage = 1;
    std::cout << "Player attacks " << target->getName() << "! Damage: " << damage << std::endl;
    target->takeDamage(damage);
}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
    std::cout << "Player takes " << amount << " damage. Health: " << health << "/" << maxHealth << std::endl;
}

void Player::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
    std::cout << "Player heals " << amount << " HP. Health: " << health << "/" << maxHealth << std::endl;
}

void Player::gainExp(int amount) {
    experience += amount;
    std::cout << "Gained " << amount << " EXP! Total: " << experience << std::endl;
    while (experience >= level * 100) {
        levelUp();
    }
}

void Player::levelUp() {
    experience -= level * 100;
    level++;
    maxHealth += 20;
    health = maxHealth;
    attackPower += 5;
    defense += 2;
    std::cout << "=== LEVEL UP! ===" << std::endl;
    std::cout << "Now level " << level << "!" << std::endl;
    std::cout << "HP: " << health << "/" << maxHealth << " | ATK: " << attackPower << " | DEF: " << defense << std::endl;
}

void Player::pickUp(Item* item) {
    inventory.push_back(item);
    std::cout << "Picked up: " << item->getName() << std::endl;
}

void Player::useItem(int index) {
    if (index >= 0 && index < (int)inventory.size()) {
        Item* item = inventory[index];
        
        if (item->getType() == "potion") {
            heal(item->getHealAmount());
            delete item;
            inventory.erase(inventory.begin() + index);
        } 
        else if (item->getType() == "weapon") {
            attackPower += item->getAttackBonus();
            std::cout << "Equipped " << item->getName() << "! ATK +" << item->getAttackBonus() << std::endl;
            std::cout << "New ATK: " << attackPower << std::endl;
            delete item;
            inventory.erase(inventory.begin() + index);
        }
        else if (item->getType() == "armor") {
            defense += item->getDefenseBonus();
            std::cout << "Equipped " << item->getName() << "! DEF +" << item->getDefenseBonus() << std::endl;
            std::cout << "New DEF: " << defense << std::endl;
            delete item;
            inventory.erase(inventory.begin() + index);
        } else {
            std::cout << "Cannot use " << item->getName() << std::endl;
        }
    }
}

void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

Player::~Player() {
    for (Item* item : inventory) {
        delete item;
    }
}