#include "Player.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 3: ПЕРЕМЕЩЕНИЕ ИГРОКА" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Player player;
    std::cout << "Игрок создан на позиции: (" << player.getX() << ", " << player.getY() << ")" << std::endl;
    
    player.setPosition(3, 4);
    std::cout << "Переместили в (3, 4)" << std::endl;
    
    if (player.getX() == 3 && player.getY() == 4) {
        std::cout << "Позиция изменилась правильно" << std::endl;
    } else {
        std::cout << "Ошибка: позиция не изменилась!" << std::endl;
        return 1;
    }
    
    player.setPosition(0, 0);
    std::cout << "Вернули в (0, 0)" << std::endl;
    
    if (player.getX() == 0 && player.getY() == 0) {
        std::cout << "Сценарий пройден: перемещение работает" << std::endl;
    } else {
        std::cout << "Ошибка: не удалось вернуться в (0,0)!" << std::endl;
        return 1;
    }
    
    return 0;
}