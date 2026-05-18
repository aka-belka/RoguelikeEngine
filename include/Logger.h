#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

class Logger {
private:
    static Logger* instance;
    std::vector<std::string> messages;
    Logger();

public:
    static Logger* getInstance();
    void write(const std::string& message);
    void saveToFile(const std::string& filename);
    void clear() { messages.clear(); }
    ~Logger();
};

#endif