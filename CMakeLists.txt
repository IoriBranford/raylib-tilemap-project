cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(rltmx)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
add_subdirectory(lib)

# Our Project
set(CMAKE_C_FLAGS "-fms-extensions")
include_directories(include)
add_executable(game
    src/engine/engine.c
    src/game/game.c
    src/main.c)
#set(raylib_VERBOSE 1)
target_link_libraries(game raylib-tmx raylib_aseprite)

# Web Configurations
if (DEFINED ${PLATFORM} AND ${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(game PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(game "-framework IOKit")
    target_link_libraries(game "-framework Cocoa")
    target_link_libraries(game "-framework OpenGL")
endif()

if(MSVC)
    foreach(VARIANT Debug Release MinSizeRel RelWithDebInfo)
        make_directory(${CMAKE_BINARY_DIR}/${VARIANT})
        file(CREATE_LINK ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/${VARIANT}/resources SYMBOLIC)
    endforeach()
else()
    file(CREATE_LINK ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources SYMBOLIC)
endif()