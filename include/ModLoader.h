#ifndef MOD_LOADER_H
#define MOD_LOADER_H

#include <string>
#include <vector>
#include "Monster.h"
#include "Item.h"

class ModLoader {
private:
    std::string modsPath;
    std::vector<std::string> loadedFiles;

public:
    ModLoader();
    void scanFolder();
    void parseFile(std::string path);
    void createObjects();
    Monster* createMonsterFromData();
    Item* createItemFromData();
};

#endif