#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "Monster.h"
#include "Item.h"

class Room {
private:
    std::string type;
    std::vector<Monster*> monsters;
    std::vector<Item*> items;

public:
    Room(std::string type);
    void addMonster(Monster* monster);
    void addItem(Item* item);
    void createMonsters();
    void createItems();
    void clearMonsters();
};

#endif