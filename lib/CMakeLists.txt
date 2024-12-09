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

add_subdirectory(LDtkLoader)

# Not using ldtk from QuickType:
# - JSON arrays become linked lists which are slow and cumbersome to traverse
# - Designed to build on/for POSIX systems only - depends on pthread and does not look for any of the available windows equivalents
# set(ENABLE_CJSON_TEST OFF)
# set(ENABLE_CJSON_UNINSTALL OFF)
# add_subdirectory(cJSON)
# add_subdirectory(c-list)
# add_subdirectory(c-hashtable)
# if(WIN32)
#     find_package(PThreads4W REQUIRED)
#     target_include_directories(list PRIVATE ${PThreads4W_INCLUDE_DIR})
#     target_link_libraries(list PThreads4W::PThreads4W)
#     target_include_directories(hashtable PRIVATE ${PThreads4W_INCLUDE_DIR})
#     target_link_libraries(hashtable PThreads4W::PThreads4W)
# endif()

# add_subdirectory(ldtk)
# target_include_directories(ldtk PUBLIC ldtk cJSON c-list/include c-hashtable/include)