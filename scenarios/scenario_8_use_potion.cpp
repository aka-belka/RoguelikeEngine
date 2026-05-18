#include "Player.h"
#include "Item.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 8: ИСПОЛЬЗОВАНИЕ ЗЕЛЬЯ" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    Item* potion = new Item("hp_pot", "Health Potion", "potion", 50, 0, 0);
    
    player.takeDamage(40);
    std::cout << "Игрок получил урон. HP=" << player.getHealth() << "/" << player.getMaxHealth() << std::endl;
    
    player.pickUp(potion);
    std::cout << "Подобрано зелье. Инвентарь: " << player.getInventory().size() << " предметов" << std::endl;
    
    int oldHealth = player.getHealth();
    player.useItem(0);
    std::cout << "Зелье использовано. HP=" << player.getHealth() << "/" << player.getMaxHealth() << std::endl;
    
    if (player.getHealth() > oldHealth) {
        std::cout << "  Зелье вылечило игрока" << std::endl;
    } else {
        std::cout << "  ОШИБКА: зелье не сработало!" << std::endl;
        return 1;
    }
    
    if (player.getInventory().empty()) {
        std::cout << "  Зелье исчезло из инвентаря" << std::endl;
    } else {
        std::cout << "  ОШИБКА: зелье осталось в инвентаре!" << std::endl;
        return 1;
    }
    
    std::cout << "\n Сценарий пройден" << std::endl;
    return 0;
}