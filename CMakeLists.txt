cmake_minimum_required(VERSION 3.1.0)

project(FoggyEngine VERSION 0.1.0)

find_package(SFML 2 COMPONENTS audio graphics window system network)
find_package(box2d REQUIRED)
find_package(Lua REQUIRED)

set(Utils_Src
    Engine/util/src/Memory.cpp)

set(Animation_Src 
    Engine/AnimationSystem/src/Animation.cpp
    Engine/AnimationSystem/src/AnimatedSprite.cpp)

set(ES_Src
    Engine/EntitySystem/Entities/src/Entity.cpp
    Engine/EntitySystem/Components/src/Collision.cpp
    Engine/EntitySystem/Components/src/Transform.cpp
    Engine/EntitySystem/Systems/src/CollisionSystem.cpp)

set(GUI_Src
    Engine/GUI/src/Widget.cpp Engine/GUI/src/Label.cpp
    Engine/GUI/src/Button.cpp Engine/GUI/src/Frame.cpp
    Engine/GUI/src/Container.cpp Engine/GUI/src/Label.cpp)

set(Engine_Src ${Utils_Src} ${ES_Src} ${Animation_Src} ${GUI_Src}
    Engine/ActionSystem/src/Action.cpp
    Engine/Camera/src/Camera.cpp
    Engine/TimerSystem/src/TimerSystem.cpp)

add_executable(foggy 
    ${Engine_Src} Game/src/main.cpp Game/src/Game.cpp 
    Game/Configuration/src/Configuration.cpp
    Game/Player/Animator/src/PlayerAnimator.cpp
    Game/Player/src/Player.cpp
    Game/Systems/src/HealthSystem.cpp)

target_link_libraries(foggy PUBLIC 
    sfml-audio sfml-graphics sfml-window sfml-system sfml-network 
    box2d 
    ${LUA_LIBRARIES})

target_include_directories(foggy PUBLIC Game Engine ${LUA_INCLUDE_DIR})

target_compile_options(foggy PUBLIC -Wall -Wextra -Wundef -pedantic)

