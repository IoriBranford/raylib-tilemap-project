set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(raylib)

add_subdirectory(tmx)

add_subdirectory(raylib-tmx/include)
add_library(raylib-tmx STATIC raylib-tmx/src/raylib-tmx.c)
set(RAYLIB_TMX_DEPS raylib tmx raylib-tmx-h)
target_link_libraries(raylib-tmx PUBLIC ${RAYLIB_TMX_DEPS})

add_subdirectory(LDtkLoader)

set(ENABLE_CJSON_TEST OFF)
set(ENABLE_CJSON_UNINSTALL OFF)
add_subdirectory(cJSON)
add_subdirectory(c-list)
add_subdirectory(c-hashtable)

add_subdirectory(ldtk)
target_include_directories(ldtk PUBLIC ldtk cJSON c-list/include c-hashtable/include)