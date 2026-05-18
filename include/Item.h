#ifndef ITEM_H
#define ITEM_H

#include <string>

class Player;

class Item {
private:
    std::string id;
    std::string name;
    std::string type;
    int healAmount;
    int attackBonus;
    int defenseBonus;

public:
    Item(const std::string& id, const std::string& name, const std::string& type, 
         int healAmount = 0, int attackBonus = 0, int defenseBonus = 0);
    Item(const Item& other);
    
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    int getHealAmount() const { return healAmount; }
    int getAttackBonus() const { return attackBonus; }
    int getDefenseBonus() const { return defenseBonus; }
};

#endif