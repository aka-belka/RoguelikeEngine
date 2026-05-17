#include "Room.h"
#include "Monster.h"
#include "ModLoader.h"
#include <iostream>

Room::Room(int x, int y, std::string type) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->isCleared = false;
}

void Room::addMonster(Monster* monster) {
    monsters.push_back(monster);
}

void Room::addItem(Item* item) {
    items.push_back(item);
}


void Room::clearMonsters() {
    for (Monster* monster : monsters) {
        delete monster;
    }
    monsters.clear();
    isCleared = true;
}

Room::~Room() {
    clearMonsters();
    for (Item* item : items) {
        delete item;
    }
}