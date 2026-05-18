#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameEngine.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    std::cout << "========================================" << std::endl;
    std::cout << "       ROGUELIKE ENGINE                 " << std::endl;
    std::cout << "========================================" << std::endl;
    
    GameEngine engine;
    engine.start();
    Logger::getInstance()->saveToFile("../game.log");
    
    return 0;
}