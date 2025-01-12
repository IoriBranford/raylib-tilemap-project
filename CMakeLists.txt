cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(rltmx)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
add_subdirectory(lib)

# Our Project
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-fms-extensions")
endif()
include_directories(include lib/chipmunk2d/include/chipmunk)
add_executable(game
    src/engine/engine.c
    src/engine/assets.c
    src/engine/gfx2d.c
    src/engine/gfx2d_text.c
    src/engine/gfx2d_tmx.c
    src/engine/tasks.c
    src/game/game.c
    src/game/confetti.c
    src/game/physics.c
    src/game/physics_tmx.c
    src/game/main.c)
#set(raylib_VERBOSE 1)
target_link_libraries(game raylib tmx raylib_aseprite chipmunk_static)

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