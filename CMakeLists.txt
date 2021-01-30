cmake_minimum_required(VERSION 3.1.0)

project(FoggyEngine VERSION 0.1.0)

find_package(SFML 2 COMPONENTS audio graphics window system network)
find_package(box2d REQUIRED)
find_package(Lua REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

set(Utils_Src Engine/util/src/Memory.cpp)

set(Resource_Src Engine/ResourceManager/src/Resource.cpp)

set(Animation_Src Engine/AnimationSystem/src/Animation.cpp
                  Engine/AnimationSystem/src/AnimatedSprite.cpp)

set(ES_Src
    Engine/EntitySystem/Entities/src/Entity.cpp
    Engine/EntitySystem/Components/src/Collision.cpp
    Engine/EntitySystem/Components/src/Transform.cpp
    Engine/EntitySystem/Components/src/LuaScript.cpp
    Engine/EntitySystem/Components/src/Skin.cpp
    Engine/EntitySystem/Systems/src/CollisionSystem.cpp
    Engine/EntitySystem/Systems/src/SkinSystem.cpp)

set(GUI_Src
    Engine/GUI/src/Widget.cpp
    Engine/GUI/src/Label.cpp
    Engine/GUI/src/Button.cpp
    Engine/GUI/src/Frame.cpp
    Engine/GUI/src/Container.cpp
    Engine/GUI/src/Layout.cpp
    Engine/GUI/src/VLayout.cpp
    Engine/GUI/src/Sprite.cpp
    Engine/GUI/src/SpriteButton.cpp
    Engine/GUI/src/Configuration.cpp)

set(TileMap_Src Engine/TileMap/src/VLayer.cpp Engine/TileMap/src/VMap.cpp
                Engine/TileMap/src/Square.cpp Engine/TileMap/src/MapViewer.cpp)

set(Engine_Src
    ${Resource_Src}
    ${Utils_Src}
    ${ES_Src}
    ${Animation_Src}
    ${GUI_Src}
    ${Lua_Src}
    ${TileMap_Src}
    Engine/ActionSystem/src/Action.cpp
    Engine/Camera/src/Camera.cpp
    Engine/TimerSystem/src/TimerSystem.cpp)

add_executable(
    foggy
    ${Engine_Src} Game/src/main.cpp Game/src/Game.cpp
    Game/Configuration/src/Configuration.cpp Game/Player/src/Player.cpp
    Game/Systems/src/HealthSystem.cpp)

target_link_libraries(
    foggy
    PUBLIC sfml-audio
           sfml-graphics
           sfml-window
           sfml-system
           sfml-network
           box2d
           ${LUA_LIBRARIES}
           ${JSONCPP_LIBRARIES})

target_include_directories(foggy PUBLIC Game Engine ${LUA_INCLUDE_DIR})

target_compile_options(foggy PUBLIC -Wall -Wextra -Wundef -pedantic -std=c++17)
