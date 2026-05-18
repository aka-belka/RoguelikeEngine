#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>

class Player;
class Item;

class Monster {
private:
    std::string id;
    std::string name;
    int maxHealth;
    int health;
    int attackPower;
    int defense;
    int expReward;
    std::vector<std::string> dropItemIds;

public:
    Monster(const std::string& id, const std::string& name, int health, int attackPower, int defense, int expReward);
    Monster(const Monster& other);
    
    void attack(Player* target);
    void takeDamage(int amount);
    void setHealth(int newHealth) { health = newHealth; maxHealth = newHealth; }
    void setAttackPower(int newAttack) { attackPower = newAttack; }
    void setExpReward(int newExp) { expReward = newExp; }
    bool isAlive() const { return health > 0; }
    
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttackPower() const { return attackPower; }
    int getExpReward() const { return expReward; }
    int getDefense() const { return defense; }
    const std::vector<std::string>& getDropItemIds() const { return dropItemIds; }
    
    void addDropItemId(const std::string& itemId);
    ~Monster();
};

#endif