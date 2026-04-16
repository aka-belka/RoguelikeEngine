#include "Room.h"
#include <iostream>

Room::Room(std::string type) {
    this->type = type;
}

void Room::addMonster(Monster* monster) {
    monsters.push_back(monster);
}

void Room::addItem(Item* item) {
    items.push_back(item);
}

void Room::createMonsters() {
    std::cout << "Creating monsters in " << type << " room..." << std::endl;
}

void Room::createItems() {
    std::cout << "Creating items in " << type << " room..." << std::endl;
}

void Room::clearMonsters() {
    monsters.clear();
    std::cout << "All monsters cleared from " << type << " room" << std::endl;
}