#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string id;
    std::string name;
    std::string type;
    int attackBonus;
    int defenseBonus;

public:
    Item(std::string id, std::string name, std::string type, int attackBonus, int defenseBonus);
    void use(class Player* target);
    std::string getName();
};

#endif