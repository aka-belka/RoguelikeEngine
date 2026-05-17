#ifndef MOD_LOADER_H
#define MOD_LOADER_H

#include <string>
#include <vector>
#include <map>
#include "Monster.h"
#include "Item.h"
#include "Room.h"

class ModLoader {
private:
    std::string modsPath;
    std::vector<Monster*> loadedMonsters;
    std::vector<Item*> loadedItems;
    std::map<std::string, Monster*> monsterMap;
    std::map<std::string, Item*> itemMap;
    
    std::string readFile(const std::string& path);
    std::map<std::string, std::string> parseJSONObject(const std::string& json);
    std::vector<std::map<std::string, std::string>> parseJSONArray(const std::string& json);
    std::vector<RoomTypeData> roomTypes;

public:
    ModLoader();
    void loadAll();
    void loadMonsters();
    void loadItems();
    void loadMonstersFromCSV();
    void loadItemsFromCSV();
    void loadRooms();
    void loadRoomsFromCSV();
    const std::vector<RoomTypeData>& getRoomTypes() const { return roomTypes; }
    bool itemExists(const std::string& id) const { return itemMap.count(id) > 0; }
    Item* createItem(const std::string& id);
    
    std::vector<Monster*> getMonsterList() const { return loadedMonsters; }
    std::vector<Item*> getItemList() const { return loadedItems; }
    ~ModLoader();
};

#endif