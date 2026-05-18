#include "Level.h"
#include "ModLoader.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 2: ГЕНЕРАЦИЯ УРОВНЯ" << std::endl;
    std::cout << "========================================" << std::endl;
    
    ModLoader loader;
    loader.loadAll();
    std::cout << "Моды загружены" << std::endl;
    
    Level level(8, 8);
    level.generate(&loader);
    std::cout << "Уровень 8×8 сгенерирован" << std::endl;
    Room* startRoom = level.getRoom(0, 0);
    if (startRoom && startRoom->getType() == "start") {
        std::cout << "Стартовая комната на позиции (0,0)" << std::endl;
    } else {
        std::cout << "Ошибка: стартовая комната не найдена!" << std::endl;
        return 1;
    }
    
    Room* bossRoom = level.getRoom(7, 7);
    if (bossRoom && bossRoom->getType() == "boss") {
        std::cout << "Босс-комната на позиции (7,7)" << std::endl;
    } else {
        std::cout << "Ошибка: босс-комната не найдена!" << std::endl;
        return 1;
    }
    
    std::cout << "Сценарий пройден: уровень сгенерирован корректно" << std::endl;
    return 0;
}