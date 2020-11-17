cmake_minimum_required(VERSION 3.1.0)

project(FoggyEngine VERSION 0.1.0)

find_package(SFML 2 COMPONENTS audio graphics window system network)
find_package(box2d REQUIRED)

set(Engine_Src 
    Engine/World/src/World.cpp
    Engine/Entity/src/Entity.cpp
    Engine/Entity/src/RectangleEntity.cpp Engine/Entity/src/CircleEntity.cpp
    Engine/ActionSystem/src/Action.cpp)

add_executable(foggy ${Engine_Src} Game/src/main.cpp Game/src/Game.cpp Game/src/Player.cpp)

target_link_libraries(foggy PUBLIC sfml-audio sfml-graphics sfml-window sfml-system sfml-network box2d)
target_compile_options(foggy PUBLIC -Wall -Wextra -Wundef -pedantic)
target_include_directories(foggy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Game Engine)

