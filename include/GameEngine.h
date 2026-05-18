#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Level.h"
#include "Player.h"
#include "ModLoader.h"
#include "Logger.h"

class GameEngine {
private:
    Level* currentLevel;
    Player* player;
    ModLoader* modLoader;
    bool isRunning;
    int currentLevelNumber;

    int startLevel;
    int dungeonWidth;
    int dungeonHeight;
    std::string modsPath;

public:
    GameEngine();
    void start();
    void loadMods();
    void gameOver();
    ~GameEngine();

    Player* getPlayer() const { return player; }
    Level* getCurrentLevel() const { return currentLevel; }
    int getCurrentLevelNumber() const { return currentLevelNumber; }
    bool isGameRunning() const { return isRunning; }
    ModLoader* getModLoader() const { return modLoader; }

    void setStartLevel(int level) { startLevel = level; currentLevelNumber = startLevel; }
    void setDungeonSize(int width, int height) { dungeonWidth = width; dungeonHeight = height; }
    void setModsPath(const std::string& path);
};

#endif