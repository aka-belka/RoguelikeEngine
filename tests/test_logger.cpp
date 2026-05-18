#include "catch.hpp"
#include "Logger.h"
#include <fstream>
#include <cstdio> 

std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    return content;
}

void deleteTestFile(const std::string& filename) {
    std::remove(filename.c_str());
}

TEST_CASE("Logger singleton pattern", "[Logger]") {
    Logger::getInstance()->clear();
    Logger* log1 = Logger::getInstance();
    Logger* log2 = Logger::getInstance();
    
    SECTION("getInstance returns same instance every time") {
        REQUIRE(log1 == log2);
    }
    
    SECTION("Logger instance is not null") {
        REQUIRE(log1 != nullptr);
    }
}

TEST_CASE("Logger write and saveToFile", "[Logger]") {
    Logger::getInstance()->clear();
    Logger* logger = Logger::getInstance();
    std::string testFile = "test_log.log";
    
    SECTION("write adds message to log") {
        logger->write("Test message 1");
        logger->saveToFile(testFile);
        
        std::string content = readFileContent(testFile);
        REQUIRE(content.find("Test message 1") != std::string::npos);
        
        deleteTestFile(testFile);
    }
    
    SECTION("Multiple messages are saved") {
        logger->write("Message A");
        logger->write("Message B");
        logger->write("Message C");
        logger->saveToFile(testFile);
        
        std::string content = readFileContent(testFile);
        REQUIRE(content.find("Message A") != std::string::npos);
        REQUIRE(content.find("Message B") != std::string::npos);
        REQUIRE(content.find("Message C") != std::string::npos);
        
        deleteTestFile(testFile);
    }
    
    SECTION("Empty log still saves (doesn't crash)") {
        logger->saveToFile(testFile);
        
        std::ifstream file(testFile);
        REQUIRE(file.good() == true);
        file.close();
        
        deleteTestFile(testFile);
    }
}

TEST_CASE("Logger saveToFile creates file with correct name", "[Logger]") {
    Logger::getInstance()->clear();
    Logger* logger = Logger::getInstance();
    std::string filename = "custom_log.log";
    
    SECTION("File is created after saveToFile") {
        logger->saveToFile(filename);
        
        std::ifstream file(filename);
        REQUIRE(file.good() == true);
        file.close();
        
        deleteTestFile(filename);
    }
    
    SECTION("File contains the messages that were written") {
        logger->write("Special message for file");
        logger->saveToFile(filename);
        
        std::string content = readFileContent(filename);
        REQUIRE(content.find("Special message for file") != std::string::npos);
        
        deleteTestFile(filename);
    }
}

TEST_CASE("Logger writes multiple times", "[Logger]") {
    Logger::getInstance()->clear();
    Logger* logger = Logger::getInstance();
    std::string testFile = "multi_test.log";
    
    SECTION("Write after save doesn't lose previous messages") {
        logger->write("First batch");
        logger->saveToFile(testFile);
        
        logger->write("Second batch");
        logger->saveToFile(testFile);
        
        std::string content = readFileContent(testFile);
        REQUIRE(content.find("First batch") != std::string::npos);
        REQUIRE(content.find("Second batch") != std::string::npos);
        
        deleteTestFile(testFile);
    }
}

TEST_CASE("Logger handles empty message", "[Logger]") {
    Logger::getInstance()->clear();
    Logger* logger = Logger::getInstance();
    std::string testFile = "empty_test.log";
    
    SECTION("Empty message can be written") {
        logger->write("");
        logger->saveToFile(testFile);
        std::ifstream file(testFile);
        REQUIRE(file.good() == true);
        file.close();
        
        deleteTestFile(testFile);
    }
}

TEST_CASE("Logger handles long messages", "[Logger]") {
    Logger::getInstance()->clear();
    Logger* logger = Logger::getInstance();
    std::string testFile = "long_test.log";
    std::string longMessage(1000, 'A'); 
    
    SECTION("Long message can be written and saved") {
        logger->write(longMessage);
        logger->saveToFile(testFile);
        
        std::string content = readFileContent(testFile);
        REQUIRE(content.find(longMessage) != std::string::npos);
        
        deleteTestFile(testFile);
    }
}

TEST_CASE("Logger destructor saves to game.log", "[Logger]") {
    Logger::getInstance()->clear();
    Logger* logger = Logger::getInstance();
    logger->write("Test for destructor");
    logger->saveToFile("destructor_test.log");
    
    std::ifstream file("destructor_test.log");
    REQUIRE(file.good() == true);
    file.close();
    
    deleteTestFile("destructor_test.log");
}