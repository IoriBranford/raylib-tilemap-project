add_subdirectory(raylib)
add_subdirectory(tmx)
add_subdirectory(raylib-tmx/include)

add_library(raylib-tmx STATIC raylib-tmx/src/raylib-tmx.c)
set(RAYLIB_TMX_DEPS raylib tmx raylib-tmx-h)
target_link_libraries(raylib-tmx PUBLIC ${RAYLIB_TMX_DEPS})
