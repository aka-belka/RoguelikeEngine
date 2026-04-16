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
    Logger* logger;
    std::string gameState;

public:
    GameEngine();
    void start();
    void loadMods();
    void update();
    ~GameEngine();
};

#endif