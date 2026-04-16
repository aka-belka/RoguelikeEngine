#include "Logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger::Logger() {
    logFile = "game.log";
}

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }
    return instance;
}

void Logger::write(std::string message) {
    messages.push_back(message);
    std::cout << "[LOG] " << message << std::endl;
}

void Logger::save() {
    // здесь можно сохранить в файл
    std::cout << "Saving log..." << std::endl;
}