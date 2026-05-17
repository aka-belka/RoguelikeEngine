#include "Level.h"
#include "ModLoader.h" 
#include "Logger.h"
#include <iostream>

Level::Level(int width, int height) {
    this->width = width;
    this->height = height;
    rooms.resize(height, std::vector<Room*>(width, nullptr));
    enemiesRemaining = 0;
}

void Level::generate(ModLoader* modLoader) {
    std::cout << "Generating level " << std::to_string(width) << "x" << std::to_string(height) << "..." << std::endl;
    Logger::getInstance()->write("Generating level " +  std::to_string(width) + "x" + std::to_string(height) + "..." );
    
    const auto& roomTypes = modLoader->getRoomTypes();
    const auto& allMonsters = modLoader->getMonsterList();
    const auto& allItems = modLoader->getItemList();
    
    enemiesRemaining = 0;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::string roomType = "normal";
            
            if (i == 0 && j == 0) {
                roomType = "start";
            } else if (i == height - 1 && j == width - 1) {
                roomType = "boss";
            } else {
                int r = std::rand() % 100;
                if (r < 15) {
                    roomType = "treasure";
                } else {
                    roomType = "normal";
                }
            }
            
            rooms[i][j] = new Room(j, i, roomType);
            Room* room = rooms[i][j];
        
            int monsterChance = 0;
            int itemChance = 0;
            bool isBoss = false;
            
            for (const auto& rt : roomTypes) {
                if (rt.type == roomType) {
                    monsterChance = rt.monsterSpawnChance;
                    itemChance = rt.itemSpawnChance;
                    isBoss = rt.isBoss;
                    break;
                }
            }
            
            if (roomType != "start" && !allMonsters.empty()) {
                int roll = std::rand() % 100;
                if (roll < monsterChance) {
                    int idx = std::rand() % allMonsters.size();
                    Monster* monster = new Monster(*allMonsters[idx]);
                    
                    if (isBoss) {
                        monster->setHealth(monster->getMaxHealth() * 3);
                        monster->setAttackPower(monster->getAttackPower() * 2);
                        monster->setExpReward(monster->getExpReward() * 3);
                        Logger::getInstance()->write("[BOSS] " + monster->getName() + " spawned!" );
                    }
                    
                    room->addMonster(monster);
                    enemiesRemaining++;
                }
            }
            
            if (!allItems.empty()) {
                int roll = std::rand() % 100;
                if (roll < itemChance) {
                    int idx = std::rand() % allItems.size();
                    Item* item = new Item(*allItems[idx]);
                    room->addItem(item);
                }
            }
        }
    }
    
    Logger::getInstance()->write("Level generated successfully with " + std::to_string(enemiesRemaining) + " enemies!" );
}

Room* Level::getRoom(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return rooms[y][x];
    }
    return nullptr;
}

void Level::enemyDefeated() {
    enemiesRemaining--;
}

Level::~Level() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete rooms[i][j];
        }
    }
}