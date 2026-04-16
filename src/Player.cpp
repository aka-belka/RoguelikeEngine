#include "Player.h"
#include "Monster.h"
#include <iostream>

Player::Player() {
    health = 100;
    x = 0;
    y = 0;
}

void Player::move(char direction) {
    switch(direction) {
        case 'w': y--; break;
        case 's': y++; break;
        case 'a': x--; break;
        case 'd': x++; break;
    }
    std::cout << "Player moved to (" << x << ", " << y << ")" << std::endl;
}

void Player::attack(Monster* target) {
    std::cout << "Player attacks " << target->getName() << "!" << std::endl;
    target->takeDamage(15);
}

void Player::pickUp(Item* item) {
    inventory.push_back(item);
    std::cout << "Player picked up: " << item->getName() << std::endl;
}

void Player::useItem(int index) {
    if (index < inventory.size()) {
        inventory[index]->use(this);
    }
}

void Player::takeDamage(int amount) {
    health -= amount;
    std::cout << "Player takes " << amount << " damage. Health: " << health << std::endl;
}

int Player::getHealth() {
    return health;
}