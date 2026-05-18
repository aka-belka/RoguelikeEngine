cmake_minimum_required(VERSION 3.14)
project(RoguelikeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(roguelike_game ${SOURCES}) 
target_include_directories(roguelike_game PRIVATE include)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_SCENARIOS "Build scenario mini-programs" ON)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(BUILD_SCENARIOS)
    add_subdirectory(scenarios)
endif()