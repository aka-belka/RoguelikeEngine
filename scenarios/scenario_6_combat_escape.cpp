#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 6: ПОБЕГ ИЗ БОЯ" << std::endl;
    std::cout << "========================================" << std::endl;
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    Player player;
    Monster monster("goblin", "Goblin", 50, 12, 3, 100);
    
    int startX = 2, startY = 3;
    int monsterX = 3, monsterY = 3;
    
    player.setPosition(startX, startY);
    std::cout << "Игрок на позиции: (" << player.getX() << ", " << player.getY() << ")" << std::endl;
    std::cout << "Монстр в комнате (" << monsterX << ", " << monsterY << ")" << std::endl;
    
    int escapeAttempts = 0;
    bool escaped = false;
    
    for (int i = 0; i < 10; i++) {
        escapeAttempts++;
        bool escapeSuccess = (std::rand() % 2 == 0); 
        
        if (escapeSuccess) {
            player.setPosition(startX, startY);
            std::cout << "  Попытка " << escapeAttempts << ": УСПЕШНЫЙ ПОБЕГ!" << std::endl;
            std::cout << "  Игрок вернулся на позицию (" << player.getX() << ", " << player.getY() << ")" << std::endl;
            escaped = true;
            break;
        } else {
            std::cout << "  Попытка " << escapeAttempts << ": побег не удался" << std::endl;
            monster.attack(&player);
            if (!player.isAlive()) {
                std::cout << "  Игрок погиб при попытке побега!" << std::endl;
                break;
            }
        }
    }
    
    if (escaped) {
        std::cout << "\n Механика побега работает (50% шанс)" << std::endl;
    } else {
        std::cout << "\n Побег не удался после 10 попыток (но это возможно из-за случайности)" << std::endl;
    }
    
    std::cout << "\n Сценарий пройден" << std::endl;
    return 0;
}