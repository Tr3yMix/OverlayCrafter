cmake_minimum_required(VERSION 3.29)
project(OverlayCrafter)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)


add_executable(OverlayCrafter src/main.cpp src/libs/tinyfiledialogs.c
        src/image_loader.cpp
        src/image_loader.h
        src/color_utils.cpp
        src/color_utils.h
        src/app.cpp
        src/app.h
        src/ColorScheme.cpp
        src/ColorScheme.h
        src/Button.cpp
        src/Button.h
)



target_compile_features(OverlayCrafter PRIVATE cxx_std_20)
target_link_libraries(OverlayCrafter PRIVATE SFML::System SFML::Window SFML::Graphics)
