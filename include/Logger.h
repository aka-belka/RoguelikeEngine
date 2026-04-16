#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

class Logger {
private:
    static Logger* instance;
    std::string logFile;
    std::vector<std::string> messages;
    Logger(); // приватный конструктор

public:
    static Logger* getInstance();
    void write(std::string message);
    void save();
};

#endif