set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(BUILD_SHARED_LIBS OFF)

option(USE_INCLUDED_RAYLIB "use raylib included as submodule in project" ON)

if(${USE_INCLUDED_RAYLIB})
    add_subdirectory(raylib)
else()
    find_package(raylib 5.5)
    if(NOT ${raylib_FOUND})
        add_subdirectory(raylib)
    endif()
endif()

add_subdirectory(tmx)

add_subdirectory(raylib-tmx/include)
add_library(raylib-tmx STATIC raylib-tmx/src/raylib-tmx.c)
set(RAYLIB_TMX_DEPS raylib tmx raylib-tmx-h)
target_link_libraries(raylib-tmx PUBLIC ${RAYLIB_TMX_DEPS})
