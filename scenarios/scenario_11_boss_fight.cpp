#include "Player.h"
#include "Monster.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 11: БОЙ С БОССОМ" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    
    Monster normal("goblin", "Goblin", 50, 12, 3, 100);
    
    Monster bossTemplate("dragon", "Dragon", 80, 15, 5, 200);
    Monster boss(bossTemplate);
    boss.setHealth(boss.getMaxHealth() * 3); 
    boss.setAttackPower(boss.getAttackPower() * 2);
    boss.setExpReward(boss.getExpReward() * 3); 
    
    std::cout << "Обычный монстр:" << std::endl;
    std::cout << "  HP=" << normal.getHealth() << ", ATK=" << normal.getAttackPower() 
              << ", EXP=" << normal.getExpReward() << std::endl;
    
    std::cout << "\nБОСС (усиленный):" << std::endl;
    std::cout << "  HP=" << boss.getHealth() << " (x3 от " << bossTemplate.getMaxHealth() << ")" << std::endl;
    std::cout << "  ATK=" << boss.getAttackPower() << " (x2 от " << bossTemplate.getAttackPower() << ")" << std::endl;
    std::cout << "  EXP=" << boss.getExpReward() << " (x3 от " << bossTemplate.getExpReward() << ")" << std::endl;
    
    if (boss.getHealth() == 240 && boss.getAttackPower() == 30 && boss.getExpReward() == 600) {
        std::cout << "\n  Босс правильно усилен!" << std::endl;
    } else {
        std::cout << "\n ОШИБКА: усиление босса работает неправильно!" << std::endl;
        return 1;
    }
    
    std::cout << "\nСценарий пройден" << std::endl;
    return 0;
}