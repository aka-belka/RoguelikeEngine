#include "Player.h"
#include "Item.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 9: ИСПОЛЬЗОВАНИЕ ОРУЖИЯ" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    Item* sword = new Item("sword", "Iron Sword", "weapon", 0, 15, 0);
    
    int oldAttack = player.getAttackPower();
    std::cout << "Сила атаки до экипировки: " << oldAttack << std::endl;
    
    player.pickUp(sword);
    player.useItem(0);
    
    std::cout << "Сила атаки после экипировки: " << player.getAttackPower() << std::endl;
    
    if (player.getAttackPower() == oldAttack + 15) {
        std::cout << "  Оружие увеличило силу атаки на 15" << std::endl;
    } else {
        std::cout << "  ОШИБКА: сила атаки изменилась неправильно!" << std::endl;
        return 1;
    }
    
    if (player.getInventory().empty()) {
        std::cout << "  Оружие исчезло из инвентаря" << std::endl;
    } else {
        std::cout << "  ОШИБКА: оружие осталось в инвентаре!" << std::endl;
        return 1;
    }
    
    std::cout << "\nСценарий пройден" << std::endl;
    return 0;
}