cmake_minimum_required(VERSION 3.1.0)

project(FoggyEngine VERSION 0.1.0)

find_package(SFML 2 COMPONENTS audio graphics window system network)

add_executable(foggy src/main.cpp src/Game.cpp)

target_link_libraries(foggy PUBLIC sfml-audio sfml-graphics sfml-window sfml-system sfml-network)
target_compile_options(foggy PUBLIC -Wall -Wextra -Wundef -pedantic)
target_include_directories(foggy PUBLIC include)

