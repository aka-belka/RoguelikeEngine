#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "GameEngine.h"

void printHelp() {
    std::cout << "Usage: roguelike_game [OPTIONS]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  --help              Show this help message" << std::endl;
    std::cout << "  --level N           Start from level N (default: 1)" << std::endl;
    std::cout << "  --width N           Dungeon width in rooms (default: 8)" << std::endl;
    std::cout << "  --height N          Dungeon height in rooms (default: 8)" << std::endl;
    std::cout << "  --mods PATH         Path to mods folder (default: ../mods/)" << std::endl;
    std::cout << std::endl;
    std::cout << "EXAMPLES:" << std::endl;
    std::cout << "  roguelike_game --level 3 --width 10 --height 10" << std::endl;
    std::cout << "  roguelike_game --mods ./custom_mods/" << std::endl;
    std::cout << "  roguelike_game --help" << std::endl;
    std::cout << std::endl;
    std::cout << "CONTROLS:" << std::endl;
    std::cout << "  w/a/s/d - move" << std::endl;
    std::cout << "  f       - fight" << std::endl;
    std::cout << "  i       - inventory" << std::endl;
    std::cout << "  p       - pickup item" << std::endl;
    std::cout << "  q       - quit" << std::endl;
}

int main(int argc, char* argv[]) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "========================================" << std::endl;
    std::cout << "       ROGUELIKE ENGINE                 " << std::endl;
    std::cout << "========================================" << std::endl;
    
    int startLevel = 1;
    int dungeonWidth = 8;
    int dungeonHeight = 8;
    std::string modsPath = "../mods/";
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            printHelp();
            return 0;
        }
        else if (arg == "--level" && i + 1 < argc) { startLevel = std::stoi(argv[++i]); }
        else if (arg == "--width" && i + 1 < argc) { dungeonWidth = std::stoi(argv[++i]); }
        else if (arg == "--height" && i + 1 < argc) { dungeonHeight = std::stoi(argv[++i]); }
        else if (arg == "--mods" && i + 1 < argc) { modsPath = argv[++i]; }
        else {
            std::cout << "Unknown argument: " << arg << std::endl;
            std::cout << "Use --help for usage information." << std::endl;
            return 1;
        }
    }
    
    GameEngine engine;
    engine.setStartLevel(startLevel);
    engine.setDungeonSize(dungeonWidth, dungeonHeight);
    engine.setModsPath(modsPath);
    
    engine.start();
    Logger::getInstance()->saveToFile("../game.log");
    
    return 0;
}