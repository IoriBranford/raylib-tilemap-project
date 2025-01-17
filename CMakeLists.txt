cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(rltmx)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
if (EMSCRIPTEN)
    set(USE_LUAJIT OFF)
endif()
add_subdirectory(lib)

# Our Project
if(MSVC)
else()
    set(CMAKE_C_FLAGS "-fms-extensions")
endif()
if(${USE_LUAJIT})
    set(LUALIBS luajit::lib luajit::header)
else()
    set(LUALIBS lua::lib lua::header)
endif ()
include_directories(include lib/chipmunk2d/include/chipmunk)

add_executable(game
    src/engine/engine.c
    src/engine/assets.c
    src/engine/gfx2d.c
    src/engine/gfx2d_text.c
    src/engine/gfx2d_tmx.c
    src/engine/lua.c
    src/engine/lua_gfx2d.c
    src/engine/lua_physics.c
    src/engine/lua_raylib.c
    src/engine/lua_task.c
    src/engine/lua_tmx.c
    src/engine/tasks.c
    src/game/game.c
    src/game/confetti.c
    src/game/confetti_tmx.c
    src/game/physics.c
    src/game/physics_tmx.c
    src/game/main.c)

#set(raylib_VERBOSE 1)
target_link_libraries(game raylib tmx raylib_aseprite chipmunk_static ${LUALIBS})

# Web Configurations
if (EMSCRIPTEN)
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
        foreach(RESOURCE_DIR lua resources)
            file(CREATE_LINK ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR} ${CMAKE_BINARY_DIR}/${VARIANT}/${RESOURCE_DIR} SYMBOLIC)
        endforeach()
    endforeach()
else()
    foreach(RESOURCE_DIR lua resources)
        file(CREATE_LINK ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR} ${CMAKE_BINARY_DIR}/${RESOURCE_DIR} SYMBOLIC)
    endforeach()

    if(EMSCRIPTEN)
        foreach(RESOURCE_DIR lua resources)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${RESOURCE_DIR}")
        endforeach()
    endif()
endif()