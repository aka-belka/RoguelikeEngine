#include "Item.h"
#include "Player.h"
#include <iostream>

Item::Item(const std::string& id, const std::string& name, const std::string& type, 
int healAmount, int attackBonus, int defenseBonus) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->healAmount = healAmount;
    this->attackBonus = attackBonus;
    this->defenseBonus = defenseBonus;
}

Item::Item(const Item& other) {
    this->id = other.id;
    this->name = other.name;
    this->type = other.type;
    this->healAmount = other.healAmount;
    this->attackBonus = other.attackBonus;
    this->defenseBonus = other.defenseBonus;
}