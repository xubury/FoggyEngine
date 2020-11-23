cmake_minimum_required(VERSION 3.1.0)

project(FoggyEngine VERSION 0.1.0)

find_package(SFML 2 COMPONENTS audio graphics window system network)
find_package(box2d REQUIRED)

set(Utils_Src
    Engine/util/src/Memory.cpp)

set(ES_Src
    Engine/EntitySystem/Entities/src/Entity.cpp
    Engine/EntitySystem/Components/src/Collision.cpp
    Engine/EntitySystem/Components/src/Transform.cpp
    Engine/EntitySystem/Systems/src/CollisionSystem.cpp)

set(Engine_Src ${Utils_Src} ${ES_Src}
    Engine/ActionSystem/src/Action.cpp
    Engine/Camera/src/Camera.cpp
    Engine/TimerSystem/src/TimerSystem.cpp)

add_executable(foggy 
    ${Engine_Src} Game/src/main.cpp Game/src/Game.cpp 
     Game/Configuration/src/Configuration.cpp
     Game/src/Player.cpp
    Game/src/HealthSystem.cpp)

target_link_libraries(foggy PUBLIC sfml-audio sfml-graphics sfml-window sfml-system sfml-network box2d)
target_compile_options(foggy PUBLIC -Wall -Wextra -Wundef -pedantic)
target_include_directories(foggy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Game Engine)

