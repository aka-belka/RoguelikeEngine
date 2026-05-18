#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "Item.h"

class ModLoader;
class Monster; 

struct RoomTypeData {
    std::string type;
    std::string name;
    int monsterSpawnChance;
    int itemSpawnChance;
    bool isBoss;
};

class Room {
private:
    int x, y;
    std::string type;
    std::vector<Monster*> monsters;
    std::vector<Item*> items;
    bool isCleared;

public:
    Room(int x, int y, std::string type);
    void addMonster(Monster* monster);
    void addItem(Item* item);
    void clearMonsters();
    void setCleared(bool cleared) { isCleared = cleared; }
    std::vector<Monster*>& getMonsters() { return monsters; }
    std::vector<Item*>& getItems() { return items; }
    std::string getType() const { return type; }
    bool isClearedRoom() const { return isCleared; }
    ~Room();
};

#endif