include(FetchContent)
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

set(ZLIB_BUILD_EXAMPLES OFF)
FetchContent_Declare(
    ZLIB
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zlib"
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(ZLIB)
add_library(ZLIB::ZLIB ALIAS zlibstatic)

set(LIBXML2_WITH_ICONV OFF)
set(LIBXML2_WITH_PROGRAMS OFF)
set(LIBXML2_WITH_PYTHON OFF)
set(LIBXML2_WITH_TESTS OFF)
FetchContent_Declare(
    LibXml2
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libxml2"
    OVERRIDE_FIND_PACKAGE
)

set(INSTALL_TMX OFF)
add_subdirectory(tmx)


add_subdirectory(raylib-aseprite)

set(LUA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lua)
add_subdirectory(luajit-cmake)

set(BUILD_DEMOS OFF)
set(BUILD_SHARED OFF)
set(BUILD_STATIC ON)
set(INSTALL_STATIC OFF)
add_subdirectory(chipmunk2d)
target_compile_definitions(chipmunk_static PRIVATE CP_USE_DOUBLES=1)
