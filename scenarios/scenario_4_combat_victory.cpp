#include "Player.h"
#include "Monster.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 4: БОЙ С МОНСТРОМ И ПОБЕДА" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    Monster monster("goblin", "Goblin", 50, 12, 3, 100);
    
    std::cout << "Игрок: HP=" << player.getHealth() << ", ATK=" << player.getAttackPower() << std::endl;
    std::cout << "Монстр: HP=" << monster.getHealth() << ", ATK=" << monster.getAttackPower() << std::endl;
    
    int oldPlayerHP = player.getHealth();
    int oldMonsterHP = monster.getHealth();
    
    player.attack(&monster);
    std::cout << "Игрок атаковал! Монстр HP=" << monster.getHealth() << std::endl;
    
    if (monster.getHealth() >= oldMonsterHP) {
        std::cout << "Ошибка: монстр не получил урон!" << std::endl;
        return 1;
    }
    
    if (monster.isAlive()) {
        monster.attack(&player);
        std::cout << "Монстр атаковал! Игрок HP=" << player.getHealth() << std::endl;
    }

    while (monster.isAlive()) {
        player.attack(&monster);
        std::cout << "Атака! Монстр HP=" << monster.getHealth() << std::endl;
    }
    
    if (!monster.isAlive()) {
        std::cout << "Монстр побеждён!" << std::endl;
        
        int oldExp = player.getExperience();
        player.gainExp(monster.getExpReward());
        std::cout << "Получено опыта: " << monster.getExpReward() << ". Всего: " << player.getExperience() << std::endl;
        
        if (player.getExperience() > oldExp) {
            std::cout << "Опыт начислен правильно" << std::endl;
        }
    }
    
    std::cout << "Сценарий пройден: бой работает" << std::endl;
    return 0;
}