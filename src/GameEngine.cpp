#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() {
    modLoader = new ModLoader();
    player = nullptr;
    currentLevel = nullptr;
    isRunning = false;
    currentLevelNumber = 1;
    Logger::getInstance()->write("GameEngine created");
}

void GameEngine::start() {
    Logger::getInstance()->write("Game started");
    loadMods();
    player = new Player();
    isRunning = true;
    
    while (isRunning && player->isAlive()) {
        std::cout << "               LEVEL " << currentLevelNumber << std::endl;
        std::cout << "========================================" << std::endl;

        if (currentLevel) delete currentLevel;
        currentLevel = new Level(8, 8);
        currentLevel->generate(modLoader);
        
        player->setPosition(0, 0);
        
        bool levelComplete = false;
        
        while (isRunning && player->isAlive() && !levelComplete) {
            int expNeeded = player->getLevel() * 100;
            int currentExp = player->getExperience();

            std::cout << "\n[HP: " << player->getHealth() << "/" << player->getMaxHealth()
                      << " | LVL: " << player->getLevel()
                      << " | EXP: " << currentExp << "/" << expNeeded << "]" << std::endl;
            std::cout << "Position: (" << player->getX() << ", " << player->getY() << ")" << std::endl;
            std::cout << "Enemies left on level: " << currentLevel->getEnemiesRemaining() << std::endl;
            std::cout << "Commands: (w/a/s/d) move, (f)ight, (i)nventory, (p)ickup, (q)uit" << std::endl;
            std::cout << "> ";
            
            std::string input;
            std::cin >> input;
            
            if (input.empty()) continue;
            
            char cmd = input[0];
            
            if (cmd == 'q') {
                isRunning = false;
                break;
            }
            else if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd') {
                int newX = player->getX();
                int newY = player->getY();
                switch(cmd) {
                    case 'w': newY++; break;
                    case 's': newY--; break;
                    case 'a': newX--; break;
                    case 'd': newX++; break;
                }
                
                if (newX >= 0 && newX < currentLevel->getWidth() && 
                    newY >= 0 && newY < currentLevel->getHeight()) {
                    
                    Room* newRoom = currentLevel->getRoom(newX, newY);
                    if (newRoom) {
                        int prevX = player->getX();
                        int prevY = player->getY();
                        bool escaped = false;
                        player->setPosition(newX, newY);
                        std::cout << "You moved to room (" << newX << ", " << newY << ")" << std::endl;
                        
                        if (newRoom->getType() == "boss") {
                            std::cout << "\n!!! YOU ENTERED THE BOSS ROOM !!!" << std::endl;
                        }
                        if (newRoom->getType() == "treasure") {
                            std::cout << "\n!!! YOU ENTERED THE TREASURE ROOM !!!" << std::endl;
                        }
                        
                        std::vector<Monster*>& monsters = newRoom->getMonsters();
                        if (!monsters.empty()) {
                            std::cout << "\n=== BATTLE ===" << std::endl;
                            while (!monsters.empty() && player->isAlive()) {
                                Monster* monster = monsters[0];
                                std::cout << "You encounter " << monster->getName() << "!" << std::endl;
                                
                                while (monster->isAlive() && player->isAlive()) {
                                    std::cout << "Your HP: " << player->getHealth()  
                                              << " (ATK:" << player->getAttackPower() << " DEF:" << player->getDefense() << ") | "
                                              << monster->getName() << " HP: " << monster->getHealth()
                                              << " (ATK:" << monster->getAttackPower() << " DEF:" << monster->getDefense() << ")" << std::endl;
                                    std::cout << "(f)ight, (r)un" << std::endl;
                                    std::cout << "> ";
                                    std::string battleInput;
                                    std::cin >> battleInput;
                                    
                                    if (battleInput == "f") {
                                        player->attack(monster);
                                        if (monster->isAlive()) {
                                            monster->attack(player);
                                        } else {
                                            player->gainExp(monster->getExpReward());
                                            currentLevel->enemyDefeated();
                                            
                                            Room* currentRoom = currentLevel->getRoom(player->getX(), player->getY());
                                            for (const std::string& itemId : monster->getDropItemIds()) {
                                                Item* item = modLoader->createItem(itemId);
                                                if (item && currentRoom) {
                                                    currentRoom->addItem(item); 
                                                    std::cout << item->getName() << " fell on the ground!" << std::endl;
                                                }
                                            }
                                            
                                            monsters.erase(monsters.begin());
                                            std::cout << monster->getName() << " defeated!" << std::endl;
                                        }
                                    } else if (battleInput == "r") {
                                        if (std::rand() % 2 == 0) {
                                            std::cout << "You escaped back to room (" << prevX << ", " << prevY << ")!" << std::endl; 
                                            player->setPosition(prevX, prevY);
                                            escaped = true;
                                            break;
                                        } else {
                                            std::cout << "Failed to escape!" << std::endl;
                                            monster->attack(player);
                                        }
                                    }
                                }
                                if (escaped) break;
                            }
                            newRoom->setCleared(true);
                            
                            if (currentLevel->getEnemiesRemaining() == 0) {
                                std::cout << "\n========================================" << std::endl;
                                std::cout << "   ALL ENEMIES DEFEATED ON THIS LEVEL!" << std::endl;
                                std::cout << "========================================" << std::endl;
                                levelComplete = true; 
                            }
                        }
                    }
                } else {
                    std::cout << "Can't move there!" << std::endl;
                }
            }
            else if (cmd == 'f') {
                Room* currentRoom = currentLevel->getRoom(player->getX(), player->getY());
                if (currentRoom && !currentRoom->getMonsters().empty()) {
                    player->attack(currentRoom->getMonsters()[0]);
                } else {
                    std::cout << "No monsters here!" << std::endl;
                }
            }
            else if (cmd == 'i') {
                std::vector<Item*>& inv = player->getInventory();
                if (inv.empty()) {
                    std::cout << "Inventory is empty!" << std::endl;
                } else {
                    std::cout << "\n=== INVENTORY ===" << std::endl;
                    for (size_t i = 0; i < inv.size(); i++) {
                        std::cout << i + 1 << ". " << inv[i]->getName() 
                                  << " (" << inv[i]->getType() << ")" << std::endl;
                    }
                    if (inv.size() == 1) {
                        std::cout << "Use item? (1) or 0 to cancel: ";
                    } else {
                        std::cout << "Use item? (1-" << inv.size() << ") or 0 to cancel: ";
                    }
                    int idx;
                    std::cin >> idx;
                    if (idx > 0 && idx <= (int)inv.size()) {
                        player->useItem(idx - 1);
                    }
                }
            }
            else if (cmd == 'p') {
                Room* currentRoom = currentLevel->getRoom(player->getX(), player->getY());
                if (currentRoom && !currentRoom->getItems().empty()) {
                    std::cout << "Items on the ground:" << std::endl;
                    for (size_t i = 0; i < currentRoom->getItems().size(); i++) {
                        std::cout << i + 1 << ". " << currentRoom->getItems()[i]->getName() << std::endl;
                    }
                    if (currentRoom->getItems().size() == 1) {
                        std::cout << "Pick up which item? (1) or 0: ";
                    } else {
                        std::cout << "Pick up which item? (1-" << currentRoom->getItems().size() << ") or 0: ";
                    }
                    int idx;
                    std::cin >> idx;
                    if (idx > 0 && idx <= (int)currentRoom->getItems().size()) {
                        Item* item = currentRoom->getItems()[idx - 1];
                        player->pickUp(item);
                        currentRoom->getItems().erase(currentRoom->getItems().begin() + (idx - 1));
                    }
                } else {
                    std::cout << "No items on the ground here!" << std::endl;
                }
            }
        }
        
        if (player->isAlive() && isRunning) {
            currentLevelNumber++;
            std::cout << "\n>>> PROCEEDING TO LEVEL " << currentLevelNumber << "! <<<" << std::endl;
        }
    }
    
    gameOver();
}

void GameEngine::loadMods() {
    Logger::getInstance()->write("Loading mods...");
    modLoader->loadAll();
    Logger::getInstance()->write("Mods loaded successfully!");
}

void GameEngine::gameOver() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "             GAME OVER                  " << std::endl;
    std::cout << "    Dungeon level reached: " << currentLevelNumber << std::endl;
    std::cout << "    Character level reached: " << player->getLevel() << std::endl;
    std::cout << "========================================" << std::endl;
    Logger::getInstance()->write("Game over");
}

GameEngine::~GameEngine() {
    delete player;
    delete currentLevel;
    delete modLoader;
    Logger::getInstance()->write("GameEngine destroyed");
}