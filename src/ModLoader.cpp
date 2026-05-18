#include "ModLoader.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

ModLoader::ModLoader(const std::string& path) : modsPath(path) {
}

std::string ModLoader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::map<std::string, std::string> ModLoader::parseJSONObject(const std::string& json) {
    std::map<std::string, std::string> result;
    std::regex pattern("\"([^\"]+)\"\\s*:\\s*\"?([^\",}]+)\"?");
    auto begin = std::sregex_iterator(json.begin(), json.end(), pattern);
    auto end = std::sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        result[(*it)[1].str()] = (*it)[2].str();
    }
    return result;
}

std::vector<std::map<std::string, std::string>> ModLoader::parseJSONArray(const std::string& json) {
    std::vector<std::map<std::string, std::string>> result;
    std::regex objectPattern("\\{([^}]+)\\}");
    auto begin = std::sregex_iterator(json.begin(), json.end(), objectPattern);
    auto end = std::sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        result.push_back(parseJSONObject((*it)[1].str()));
    }
    return result;
}

void ModLoader::loadAll() {
    loadRoomsFromCSV(); 
    loadRooms();
    loadItemsFromCSV();
    loadItems();
    loadMonstersFromCSV(); 
    loadMonsters();        
}

void ModLoader::loadMonsters() {
    Logger::getInstance()->write("Loading monsters.json...");
    std::string content = readFile(modsPath + "monsters.json");
    if (content.empty()) {
        Logger::getInstance()->write("monsters.json not found, using default monsters");
        Monster* goblin = new Monster("goblin", "Goblin", 40, 12, 3, 50);
        goblin->addDropItemId("health_potion");
        loadedMonsters.push_back(goblin);
        monsterMap["goblin"] = goblin;
        return;
    }
    
    auto monsters = parseJSONArray(content);

    for (const auto& data : monsters) {
        try {
            std::string id = data.at("id");
            std::string name = data.at("name");
            int health = std::stoi(data.at("health"));
            int attack = std::stoi(data.at("attack"));
            int defense = std::stoi(data.at("defense"));
            int exp = std::stoi(data.at("expReward"));

            if (id.empty() || name.empty()) {
                throw std::runtime_error("Missing required fields (id or name)");
            }
            
            if (health <= 0) {
                throw std::runtime_error("Health must be positive, got " + std::to_string(health));
            }
            if (attack < 0) {
                throw std::runtime_error("Attack cannot be negative, got " + std::to_string(attack));
            }
            if (defense < 0) {
                throw std::runtime_error("Defense cannot be negative, got " + std::to_string(defense));
            }
            if (exp < 0) {
                throw std::runtime_error("ExpReward cannot be negative, got " + std::to_string(exp));
            }
            
            Monster* monster = new Monster(id, name, health, attack, defense, exp);
            if (data.count("drops")) {
                std::string dropsStr = data.at("drops");
                std::stringstream ss(dropsStr);
                std::string itemId;
                while (std::getline(ss, itemId, ',')) {
                    if (itemExists(itemId)) {
                        monster->addDropItemId(itemId);
                    } else {
                        Logger::getInstance()->write("WARNING: Drop item '" + itemId + "' not found in items.json, skipping");
                    }
                }
            }
            
            loadedMonsters.push_back(monster);
            monsterMap[id] = monster;
            Logger::getInstance()->write("  Loaded monster from JSON: " + name);
        } catch (const std::exception& e) {
            Logger::getInstance()->write("Failed to parse monster: " + std::string(e.what()));
        }
    }
    Logger::getInstance()->write("Loaded " + std::to_string(loadedMonsters.size()) + " monsters");
}

void ModLoader::loadItems() {
    Logger::getInstance()->write("Loading items.json...");
    
    std::string content = readFile(modsPath + "items.json");
    if (content.empty()) {
        Logger::getInstance()->write("items.json not found, using default items");
        Item* potion = new Item("health_potion", "Health Potion", "potion", 50);
        loadedItems.push_back(potion);
        itemMap["health_potion"] = potion;
        return;
    }
    auto items = parseJSONArray(content);
    for (const auto& data : items) {
        try {
            std::string id = data.at("id");
            std::string name = data.at("name");
            std::string type = data.at("type");
            int healAmount = data.count("healAmount") ? std::stoi(data.at("healAmount")) : 0;
            int attackBonus = data.count("attackBonus") ? std::stoi(data.at("attackBonus")) : 0;
            int defenseBonus = data.count("defenseBonus") ? std::stoi(data.at("defenseBonus")) : 0;

            if (id.empty() || name.empty() || type.empty()) {
                throw std::runtime_error("Missing required fields (id, name or type)");
            }

            std::vector<std::string> validTypes = {"potion", "weapon", "armor", "misc"};
            bool isValidType = false;
            for (const auto& validType : validTypes) {
                if (type == validType) {
                    isValidType = true;
                    break;
                }
            }
            if (!isValidType) {
                throw std::runtime_error("Invalid item type: '" + type + "'. Must be potion, weapon, armor or misc");
            }

            if (healAmount < 0) {
                throw std::runtime_error("HealAmount cannot be negative, got " + std::to_string(healAmount));
            }
            if (attackBonus < 0) {
                throw std::runtime_error("AttackBonus cannot be negative, got " + std::to_string(attackBonus));
            }
            if (defenseBonus < 0) {
                throw std::runtime_error("DefenseBonus cannot be negative, got " + std::to_string(defenseBonus));
            }
            
            Item* item = new Item(id, name, type, healAmount, attackBonus, defenseBonus);
            loadedItems.push_back(item);
            itemMap[id] = item;
            Logger::getInstance()->write("  Loaded item from JSON: " + name);
        } catch (const std::exception& e) {
            Logger::getInstance()->write("Failed to parse item: " + std::string(e.what()));
        }
    }
    Logger::getInstance()->write("Loaded " + std::to_string(loadedItems.size()) + " items");
}

void ModLoader::loadRooms() {
    Logger::getInstance()->write("Loading rooms.json...");
    std::string path = modsPath + "rooms.json";
    std::ifstream file(path);
    
    if (!file.is_open()) {
        Logger::getInstance()->write("[WARN] rooms.json not found, using default room types");
        if (roomTypes.empty()) {
            roomTypes.push_back({"start", "Starting Room", 0, 0, false});
            roomTypes.push_back({"normal", "Normal Room", 70, 20, false});
            roomTypes.push_back({"treasure", "Treasure Room", 30, 100, false});
            roomTypes.push_back({"boss", "Boss Room", 100, 0, true});
        }
        return;
    }
    
    try {
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line;
        }
        file.close();
        
        if (content.empty()) {
            throw std::runtime_error("rooms.json is empty");
        }
        
        std::regex pattern("\"type\"\\s*:\\s*\"([^\"]+)\"\\s*,\\s*\"name\"\\s*:\\s*\"([^\"]+)\"\\s*,\\s*\"monsterSpawnChance\"\\s*:\\s*(\\d+)\\s*,\\s*\"itemSpawnChance\"\\s*:\\s*(\\d+)\\s*,\\s*\"isBoss\"\\s*:\\s*(true|false)");
        
        auto begin = std::sregex_iterator(content.begin(), content.end(), pattern);
        auto end = std::sregex_iterator();
        
        int roomsLoaded = 0;
        int roomsFailed = 0;
        
        for (auto it = begin; it != end; ++it) {
            try {
                RoomTypeData room;
                room.type = (*it)[1].str();
                room.name = (*it)[2].str();
                room.monsterSpawnChance = std::stoi((*it)[3].str());
                room.itemSpawnChance = std::stoi((*it)[4].str());
                room.isBoss = ((*it)[5].str() == "true");
                
                std::vector<std::string> validTypes = {"start", "normal", "treasure", "boss"};
                bool isValidType = false;
                for (const auto& validType : validTypes) {
                    if (room.type == validType) {
                        isValidType = true;
                        break;
                    }
                }
                if (!isValidType) {
                    throw std::runtime_error("Invalid room type: '" + room.type + "'. Must be start, normal, treasure or boss");
                }

                if (room.monsterSpawnChance < 0 || room.monsterSpawnChance > 100) {
                    throw std::runtime_error("monsterSpawnChance must be 0-100, got " + std::to_string(room.monsterSpawnChance));
                }
                if (room.itemSpawnChance < 0 || room.itemSpawnChance > 100) {
                    throw std::runtime_error("itemSpawnChance must be 0-100, got " + std::to_string(room.itemSpawnChance));
                }
                
                roomTypes.push_back(room);
                roomsLoaded++;
                Logger::getInstance()->write("Loaded room type: " + room.name + " (" + room.type + ")");
                
            } catch (const std::exception& e) {
                roomsFailed++;
                Logger::getInstance()->write("ERROR parsing room object: " + std::string(e.what()) + " - skipping");
            }
        }
        
        Logger::getInstance()->write("Loaded " + std::to_string(roomsLoaded) + " room types from JSON, " + std::to_string(roomsFailed) + " failed");
        if (roomTypes.empty()) {
            Logger::getInstance()->write("No valid rooms loaded from JSON, using defaults");
            roomTypes.push_back({"start", "Starting Room", 0, 0, false});
            roomTypes.push_back({"normal", "Normal Room", 70, 20, false});
            roomTypes.push_back({"treasure", "Treasure Room", 30, 100, false});
            roomTypes.push_back({"boss", "Boss Room", 100, 0, true});
        }
        
    } catch (const std::exception& e) {
        Logger::getInstance()->write("FATAL ERROR loading rooms.json: " + std::string(e.what()));
        if (roomTypes.empty()) {
            Logger::getInstance()->write("Using default room types as fallback");
            roomTypes.push_back({"start", "Starting Room", 0, 0, false});
            roomTypes.push_back({"normal", "Normal Room", 70, 20, false});
            roomTypes.push_back({"treasure", "Treasure Room", 30, 100, false});
            roomTypes.push_back({"boss", "Boss Room", 100, 0, true});
        }
    }
}

void ModLoader::loadRoomsFromCSV() {
    Logger::getInstance()->write("Loading rooms from CSV...");
    std::string path = modsPath + "rooms.csv";
    std::ifstream file(path);
    if (!file.is_open()) {
        Logger::getInstance()->write("No rooms.csv found, using JSON only");
        return;
    }
    
    std::string line;
    bool firstLine = true;
    int lineNumber = 1;
    
    while (std::getline(file, line)) {
        lineNumber++;
        if (firstLine) { firstLine = false; continue; }
        if (line.empty()) continue;
        
        try {
            std::stringstream ss(line);
            std::string type, name, monsterChanceStr, itemChanceStr, isBossStr;
            
            std::getline(ss, type, ',');
            std::getline(ss, name, ',');
            std::getline(ss, monsterChanceStr, ',');
            std::getline(ss, itemChanceStr, ',');
            std::getline(ss, isBossStr, ',');
            
            if (type.empty() || name.empty()) {
                throw std::runtime_error("Missing required fields (type or name)");
            }
            
            RoomTypeData room;
            room.type = type;
            room.name = name;
            room.monsterSpawnChance = std::stoi(monsterChanceStr);
            room.itemSpawnChance = std::stoi(itemChanceStr);
            room.isBoss = (isBossStr == "true" || isBossStr == "1");

            std::vector<std::string> validTypes = {"start", "normal", "treasure", "boss"};
            bool isValidType = false;
            for (const auto& validType : validTypes) {
                if (room.type == validType) {
                    isValidType = true;
                    break;
                }
            }
            if (!isValidType) {
                throw std::runtime_error("Invalid room type: '" + room.type + "'");
            }
            if (room.monsterSpawnChance < 0 || room.monsterSpawnChance > 100) {
                throw std::runtime_error("monsterSpawnChance must be 0-100, got " + std::to_string(room.monsterSpawnChance));
            }
            if (room.itemSpawnChance < 0 || room.itemSpawnChance > 100) {
                throw std::runtime_error("itemSpawnChance must be 0-100, got " + std::to_string(room.itemSpawnChance));
            }

            roomTypes.push_back(room);
            Logger::getInstance()->write("Loaded room type from CSV: " + room.name);
            
        } catch (const std::exception& e) {
            Logger::getInstance()->write("ERROR in rooms.csv line " + std::to_string(lineNumber) + ": " + std::string(e.what()) + " - skipping");
        }
    }
}
void ModLoader::loadMonstersFromCSV() {
    Logger::getInstance()->write("Loading monsters.csv...");
    std::string path = modsPath + "monsters.csv";
    std::ifstream file(path);
    if (!file.is_open()) {
        Logger::getInstance()->write("No monsters.csv found, using JSON only");
        return;
    }
    
    std::string line;
    bool firstLine = true;
    int lineNumber = 1;
    
    while (std::getline(file, line)) {
        lineNumber++;
        if (firstLine) { firstLine = false; continue; }
        if (line.empty()) continue;
        
        try {
            std::stringstream ss(line);
            std::string id, name, healthStr, attackStr, defenseStr, expStr, dropsStr;
            
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, healthStr, ',');
            std::getline(ss, attackStr, ',');
            std::getline(ss, defenseStr, ',');
            std::getline(ss, expStr, ',');
            std::getline(ss, dropsStr, ',');
            
            if (id.empty() || name.empty()) {
                throw std::runtime_error("Missing required fields (id or name)");
            }
            
            int health = std::stoi(healthStr);
            int attack = std::stoi(attackStr);
            int defense = std::stoi(defenseStr);
            int exp = std::stoi(expStr);
            
            Monster* monster = new Monster(id, name, health, attack, defense, exp);

            std::stringstream dropSs(dropsStr);
            std::string dropId;
            while (std::getline(dropSs, dropId, ';')) {
                if (!dropId.empty()) {
                    if (itemExists(dropId)) {
                        monster->addDropItemId(dropId);
                    } else {
                        Logger::getInstance()->write("WARNING: Drop item '" + dropId + "' not found in items, skipping");
                    }
                }
            }

            if (health <= 0) {
                throw std::runtime_error("Health must be positive, got " + std::to_string(health));
            }
            if (attack < 0) {
                throw std::runtime_error("Attack cannot be negative, got " + std::to_string(attack));
            }
            if (defense < 0) {
                throw std::runtime_error("Defense cannot be negative, got " + std::to_string(defense));
            }
            if (exp < 0) {
                throw std::runtime_error("ExpReward cannot be negative, got " + std::to_string(exp));
            }
            
            loadedMonsters.push_back(monster);
            monsterMap[id] = monster;
            Logger::getInstance()->write("Loaded monster from CSV: " + name);
            
        } catch (const std::exception& e) {
            Logger::getInstance()->write("ERROR in monsters.csv line " + std::to_string(lineNumber) + ": " + std::string(e.what()) + " - skipping");
        }
    }
}

void ModLoader::loadItemsFromCSV() {
    Logger::getInstance()->write("Loading items.csv...");
    std::string path = modsPath + "items.csv";
    std::ifstream file(path);
    if (!file.is_open()) {
        Logger::getInstance()->write("No items.csv found, using JSON only");
        return;
    }
    
    std::string line;
    bool firstLine = true;
    int lineNumber = 1;
    
    while (std::getline(file, line)) {
        lineNumber++;
        if (firstLine) { firstLine = false; continue; }
        if (line.empty()) continue;
        
        try {
            std::stringstream ss(line);
            std::string id, name, type, healStr, attackBonusStr, defenseBonusStr;
            
            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, type, ',');
            std::getline(ss, healStr, ',');
            std::getline(ss, attackBonusStr, ',');
            std::getline(ss, defenseBonusStr, ',');
            
            std::vector<std::string> validTypes = {"potion", "weapon", "armor", "misc"};
            bool isValidType = false;
            for (const auto& validType : validTypes) {
                if (type == validType) {
                    isValidType = true;
                    break;
                }
            }

            if (id.empty() || name.empty() || type.empty()) {
                throw std::runtime_error("Missing required fields (id, name or type)");
            }
            if (!isValidType) {
                throw std::runtime_error("Invalid item type: '" + type + "'. Must be potion, weapon, armor or misc");
            }
            
            int healAmount = healStr.empty() ? 0 : std::stoi(healStr);
            int attackBonus = attackBonusStr.empty() ? 0 : std::stoi(attackBonusStr);
            int defenseBonus = defenseBonusStr.empty() ? 0 : std::stoi(defenseBonusStr);
            
            Item* item = new Item(id, name, type, healAmount, attackBonus, defenseBonus);
            if (healAmount < 0) {
                throw std::runtime_error("HealAmount cannot be negative, got " + std::to_string(healAmount));
            }
            if (attackBonus < 0) {
                throw std::runtime_error("AttackBonus cannot be negative, got " + std::to_string(attackBonus));
            }
            if (defenseBonus < 0) {
                throw std::runtime_error("DefenseBonus cannot be negative, got " + std::to_string(defenseBonus));
            }
            
            loadedItems.push_back(item);
            itemMap[id] = item;
            Logger::getInstance()->write("Loaded item from CSV: " + name);
            
        } catch (const std::exception& e) {
            Logger::getInstance()->write("ERROR in items.csv line " + std::to_string(lineNumber) + ": " + std::string(e.what()) + " - skipping");
        }
    }
}

Item* ModLoader::createItem(const std::string& id) {
    if (itemMap.count(id)) {
        return new Item(*itemMap[id]);
    }
    if (!loadedItems.empty()) {
        return new Item(*loadedItems[0]);
    }
    return new Item("default", "Item", "misc");
}

ModLoader::~ModLoader() {
    for (Monster* monster : loadedMonsters) {
        delete monster;
    }
    for (Item* item : loadedItems) {
        delete item;
    }
}