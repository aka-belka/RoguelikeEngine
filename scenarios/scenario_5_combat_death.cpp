#include "Player.h"
#include "Monster.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 5: БОЙ И СМЕРТЬ ИГРОКА" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    Monster boss("dragon", "Dragon", 200, 50, 20, 500);
    
    std::cout << "Игрок: HP=" << player.getHealth() << std::endl;
    std::cout << "Дракон: HP=" << boss.getHealth() << ", ATK=" << boss.getAttackPower() << std::endl;
    
    int battleRound = 1;
    while (player.isAlive() && boss.isAlive()) {
        std::cout << "\nРаунд " << battleRound++ << ":" << std::endl;

        player.attack(&boss);
        std::cout << "  Игрок атакует! Дракон HP=" << boss.getHealth() << std::endl;
        
        if (boss.isAlive()) {
            boss.attack(&player);
            std::cout << "  Дракон атакует! Игрок HP=" << player.getHealth() << std::endl;
        }
        
        if (!player.isAlive()) {
            std::cout << "\n Игрок погиб!" << std::endl;
            break;
        }
    }
    
    if (!player.isAlive()) {
        std::cout << "Механика смерти игрока работает корректно" << std::endl;
    }
    
    std::cout << "\nСценарий пройден" << std::endl;
    return 0;
}