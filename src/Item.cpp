#include "Item.h"
#include "Player.h"
#include <iostream>

Item::Item(std::string id, std::string name, std::string type, int attackBonus, int defenseBonus) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->attackBonus = attackBonus;
    this->defenseBonus = defenseBonus;
}

void Item::use(Player* target) {
    std::cout << "Using item: " << name << std::endl;
}

std::string Item::getName() {
    return name;
}