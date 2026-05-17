#include "Logger.h"
#include <iostream>
#include <fstream>

Logger* Logger::instance = nullptr;

Logger::Logger() {}

Logger* Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }
    return instance;
}

void Logger::write(const std::string& message) {
    messages.push_back(message);
}

void Logger::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& msg : messages) {
            file << msg << std::endl;
        }
        file.close();
    }
}

Logger::~Logger() {
    saveToFile("../game.log");
}