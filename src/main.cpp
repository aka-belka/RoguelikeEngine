#include <iostream>
#include "GameEngine.h"

int main() {
    std::cout << "Roguelike Engine v1.0" << std::endl;
    std::cout << "Starting game engine..." << std::endl;
    
    GameEngine engine;
    engine.start();
    
    return 0;
}