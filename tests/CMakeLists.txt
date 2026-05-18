file(GLOB SOURCES "../src/*.cpp")
foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(FILENAME ${SOURCE_FILE} NAME)
    if(NOT FILENAME STREQUAL "main.cpp")
        list(APPEND SOURCES_FILTERED ${SOURCE_FILE})
    endif()
endforeach()

file(GLOB TEST_SOURCES "test_*.cpp")
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp")

add_executable(roguelike_tests 
    test_main.cpp
    ${TEST_SOURCES}
    ${SOURCES_FILTERED}
)

target_include_directories(roguelike_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(CTest)
add_test(NAME RoguelikeUnitTests COMMAND roguelike_tests)