cmake_minimum_required(VERSION 3.29)
project(OverlayCrafter)

#C++ Standard
set(CMAKE_CXX_STANDARD 20)

#Output binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# === Resource Directory Macro ===
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/src/resources")
add_compile_definitions(RESOURCE_DIR="${RESOURCE_DIR}")

# === External Libraries ===

## Native File Dialog (NFD)
set(NFD_SOURCES
        external/nfd/nfd_common.c
        external/nfd/nfd_common.h
        external/nfd/nfd_win.cpp
)

add_library(nfd STATIC ${NFD_SOURCES})
target_include_directories(nfd PUBLIC external/nfd/include)

## === FetchContent ===
include(FetchContent)

## SFML (via FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)

## zlib (via FetchContent)

FetchContent_Declare(
        zlib
        URL https://zlib.net/zlib-1.3.1.tar.gz
)

FetchContent_MakeAvailable(zlib)

## minizip-ng (via FetchContent)

FetchContent_Declare(
        minizip
        GIT_REPOSITORY https://github.com/zlib-ng/minizip-ng.git
        GIT_TAG 4.0.10
)

set(MZ_INSTALL OFF CACHE BOOL "" FORCE)
set(MZ_FETCH_LIBS OFF CACHE BOOL "" FORCE)

#Make FetchContent Available

FetchContent_MakeAvailable(SFML minizip)

# === Source Files ===
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/main/*.cpp src/main/*.h)

# === Executable ===
add_executable(OverlayCrafter ${SRC_FILES})

# === Dependencies ===
target_link_libraries(OverlayCrafter PRIVATE SFML::System SFML::Window SFML::Graphics nfd minizip)

# === Include Directories ===
target_include_directories(OverlayCrafter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main)

# === Compile Features ===
target_compile_features(OverlayCrafter PRIVATE cxx_std_20)


