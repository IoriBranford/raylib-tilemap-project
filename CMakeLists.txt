cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(example)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
add_subdirectory(lib)

# Our Project
add_executable(${PROJECT_NAME} raylib-tmx-example.c)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib-tmx)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

file(CREATE_LINK ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources SYMBOLIC)