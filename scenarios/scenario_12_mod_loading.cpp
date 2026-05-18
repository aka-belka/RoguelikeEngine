#include "ModLoader.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "СЦЕНАРИЙ 12: ЗАГРУЗКА МОДОВ ИЗ JSON" << std::endl;
    std::cout << "========================================" << std::endl;
    
    ModLoader loader;
    loader.loadAll();
    
    const auto& monsters = loader.getMonsterList();
    std::cout << "Всего монстров: " << monsters.size() << std::endl;
    
    if (monsters.empty()) {
        std::cout << "  ВНИМАНИЕ: монстры не загружены! Проверь файл monsters.json" << std::endl;
    } else {
        for (const auto& m : monsters) {
            std::cout << "  - " << m->getName() 
                      << " (ID: " << m->getId() 
                      << ", HP: " << m->getHealth() 
                      << ", ATK: " << m->getAttackPower()
                      << ", DEF: " << m->getDefense()
                      << ", EXP: " << m->getExpReward() << ")" << std::endl;
            
            const auto& drops = m->getDropItemIds();
            if (!drops.empty()) {
                std::cout << "    Дроп: ";
                for (const auto& drop : drops) {
                    std::cout << drop << " ";
                }
                std::cout << std::endl;
            }
        }
        std::cout << "  Монстры успешно загружены из monsters.json" << std::endl;
    }
    
    const auto& items = loader.getItemList();
    std::cout << "Всего предметов: " << items.size() << std::endl;
    
    if (items.empty()) {
        std::cout << " ВНИМАНИЕ: предметы не загружены! Проверь файл items.json" << std::endl;
    } else {
        for (const auto& item : items) {
            std::cout << "  - " << item->getName() 
                      << " (ID: " << item->getId()
                      << ", Тип: " << item->getType()
                      << ", Лечение: " << item->getHealAmount()
                      << ", ATK бонус: " << item->getAttackBonus()
                      << ", DEF бонус: " << item->getDefenseBonus() << ")" << std::endl;
        }
        std::cout << "  Предметы успешно загружены из items.json" << std::endl;
    }
    
    const auto& rooms = loader.getRoomTypes();
    std::cout << "Всего типов комнат: " << rooms.size() << std::endl;
    
    if (rooms.empty()) {
        std::cout << " ВНИМАНИЕ: комнаты не загружены! Проверь файл rooms.json" << std::endl;
    } else {
        for (const auto& room : rooms) {
            std::cout << "  - " << room.name 
                      << " (Тип: " << room.type 
                      << ", Шанс монстров: " << room.monsterSpawnChance << "%"
                      << ", Шанс предметов: " << room.itemSpawnChance << "%"
                      << ", Босс: " << (room.isBoss ? "да" : "нет") << ")" << std::endl;
        }
        std::cout << " Типы комнат успешно загружены из rooms.json" << std::endl;
    }
    
    if (!items.empty()) {
        std::string testId = items[0]->getId();
        if (loader.itemExists(testId)) {
            std::cout << "  itemExists(\"" << testId << "\") вернул true" << std::endl;
        } else {
            std::cout << "  ОШИБКА: itemExists(\"" << testId << "\") вернул false!" << std::endl;
        }
    }
    
    if (!items.empty()) {
        std::string testId = items[0]->getId();
        Item* newItem = loader.createItem(testId);
        if (newItem != nullptr) {
            std::cout << "  createItem(\"" << testId << "\") создал предмет: " << newItem->getName() << std::endl;
            delete newItem;
        } else {
            std::cout << "  ОШИБКА: createItem вернул nullptr!" << std::endl;
        }
    }
    
    Item* defaultItem = loader.createItem("non_existent_id_12345");
    if (defaultItem != nullptr) {
        std::cout << " createItem(\"non_existent_id\") вернул предмет по умолчанию: " 
                  << defaultItem->getName() << std::endl;
        delete defaultItem;
    }
    std::cout << "\nСценарий пройден" << std::endl;
    return 0;
}