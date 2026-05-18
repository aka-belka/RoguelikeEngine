#include "Level.h"
#include "ModLoader.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 10: ПРОХОЖДЕНИЕ УРОВНЯ" << std::endl;
    std::cout << "========================================" << std::endl;
    
    ModLoader loader;
    loader.loadAll();
    
    Level level(5, 5);
    level.generate(&loader);
    
    std::cout << "Сгенерирован уровень 5x5" << std::endl;
    std::cout << "Монстров на уровне: " << level.getEnemiesRemaining() << std::endl;
    
    int enemiesKilled = 0;
    int initialEnemies = level.getEnemiesRemaining();
    
    for (int i = 0; i < level.getHeight(); i++) {
        for (int j = 0; j < level.getWidth(); j++) {
            Room* room = level.getRoom(j, i);
            if (room) {
                auto& monsters = room->getMonsters();
                while (!monsters.empty()) {
                    delete monsters[0];
                    monsters.erase(monsters.begin());
                    level.enemyDefeated();
                    enemiesKilled++;
                    std::cout << "  Убит монстр в комнате (" << j << "," << i << "). Осталось: " << level.getEnemiesRemaining() << std::endl;
                }
            }
        }
    }
    
    std::cout << "\nУбито монстров: " << enemiesKilled << " из " << initialEnemies << std::endl;
    
    if (level.getEnemiesRemaining() == 0) {
        std::cout << "  Все монстры на уровне побеждены!" << std::endl;
        std::cout << "  Уровень пройден, можно переходить на следующий" << std::endl;
    } else {
        std::cout << "  ОШИБКА: остались непобеждённые монстры!" << std::endl;
        return 1;
    }
    
    std::cout << "\nСценарий пройден" << std::endl;
    return 0;
}