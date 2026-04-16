cmake_minimum_required(VERSION 3.10)
project(RoguelikeEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/Monster.cpp
    src/Player.cpp
    src/Item.cpp
    src/Room.cpp
    src/Level.cpp
    src/GameEngine.cpp
    src/ModLoader.cpp
    src/Logger.cpp
)

add_executable(RoguelikeEngine ${SOURCES})