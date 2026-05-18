#include "Player.h"
#include "Item.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 7: ПОДБОР ПРЕДМЕТА" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    Item* sword = new Item("sword", "Iron Sword", "weapon", 0, 15, 0);
    
    std::cout << "Инвентарь до подбора: " << player.getInventory().size() << " предметов" << std::endl;
    
    player.pickUp(sword);
    std::cout << "Подобран предмет: " << sword->getName() << std::endl;
    
    if (player.getInventory().size() == 1) {
        std::cout << "  Предмет добавлен в инвентарь" << std::endl;
        std::cout << "  Предмет в инвентаре: " << player.getInventory()[0]->getName() << std::endl;
    } else {
        std::cout << "  ОШИБКА: предмет не добавлен в инвентарь!" << std::endl;
        return 1;
    }
    
    std::cout << "\nСценарий пройден" << std::endl;
    return 0;
}