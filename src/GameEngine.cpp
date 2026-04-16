#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine() {
    gameState = "stopped";
    modLoader = new ModLoader();
    logger = Logger::getInstance();
    logger->write("GameEngine created");
}

void GameEngine::start() {
    std::cout << "Starting game..." << std::endl;
    logger->write("Game started");
    
    loadMods();
    
    currentLevel = new Level(10);
    currentLevel->generate();
    
    player = new Player();
    
    gameState = "running";
    update();
}

void GameEngine::loadMods() {
    std::cout << "Loading mods..." << std::endl;
    logger->write("Loading mods...");
    modLoader->scanFolder();
    modLoader->parseFile("mods/test.json");
    modLoader->createObjects();
    logger->write("Mods loaded successfully");
}

void GameEngine::update() {
    std::cout << "Game is running. Press any key to continue..." << std::endl;
    gameState = "stopped";
}

GameEngine::~GameEngine() {
    delete currentLevel;
    delete player;
    delete modLoader;
    logger->write("GameEngine destroyed");
}