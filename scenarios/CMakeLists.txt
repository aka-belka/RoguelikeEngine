file(GLOB SOURCES "../src/*.cpp")

foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(FILENAME ${SOURCE_FILE} NAME)
    if(NOT FILENAME STREQUAL "main.cpp")
        list(APPEND SOURCES_FILTERED ${SOURCE_FILE})
    endif()
endforeach()

file(GLOB SCENARIO_SOURCES "scenario_*.cpp")

foreach(SCENARIO_SOURCE ${SCENARIO_SOURCES})
    get_filename_component(SCENARIO_NAME ${SCENARIO_SOURCE} NAME_WE)
    
    message(STATUS "Adding scenario: ${SCENARIO_NAME}")
    
    add_executable(${SCENARIO_NAME} ${SCENARIO_SOURCE} ${SOURCES_FILTERED})
    target_include_directories(${SCENARIO_NAME} PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
    )
endforeach()