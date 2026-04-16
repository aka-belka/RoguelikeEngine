#include "ModLoader.h"
#include <iostream>

ModLoader::ModLoader() {
    modsPath = "./mods/";
}

void ModLoader::scanFolder() {
    std::cout << "Scanning folder: " << modsPath << std::endl;
    loadedFiles.push_back("monster1.json");
    loadedFiles.push_back("item1.json");
}

void ModLoader::parseFile(std::string path) {
    std::cout << "Parsing file: " << path << std::endl;
}

void ModLoader::createObjects() {
    std::cout << "Creating objects from loaded data..." << std::endl;
}

Monster* ModLoader::createMonsterFromData() {
    std::cout << "Creating monster from JSON data..." << std::endl;
    return new Monster("001", "Goblin", 50, 10, 5);
}

Item* ModLoader::createItemFromData() {
    std::cout << "Creating item from JSON data..." << std::endl;
    return new Item("p001", "Health Potion", "consumable", 0, 0);
}