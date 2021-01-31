#include "Configuration/Configuration.hpp"

#include <sol/sol.hpp>

#include "ResourceManager/Resource.hpp"

foggy::ActionMap<int> Configuration::player_inputs;
foggy::ResourceManager<foggy::as::Animation, int> Configuration::player_anims;

foggy::ActionMap<int> Configuration::map_inputs;

Configuration::__Initializer Configuration::__initializer__;

void Configuration::init() {
    foggy::Resource::lua().set_function("C_loadAnimation", loadPlayerAnimation);
    foggy::Resource::instance().runSrcipt("res/scripts/Animation.lua");
    foggy::Resource::lua()["initAnimation"]();
    initializePlayerInputs();
}

void Configuration::initializePlayerInputs() {
    player_inputs.map(PlayerInput::Up, foggy::Action(sf::Keyboard::W));
    player_inputs.map(PlayerInput::Down, foggy::Action(sf::Keyboard::S));
    player_inputs.map(PlayerInput::Down_Realeased,
                      foggy::Action(sf::Keyboard::S, foggy::Action::Released));
    player_inputs.map(PlayerInput::Right, foggy::Action(sf::Keyboard::D));
    player_inputs.map(PlayerInput::Left, foggy::Action(sf::Keyboard::A));
    player_inputs.map(PlayerInput::Attack, foggy::Action(sf::Keyboard::J));
}

void Configuration::loadPlayerAnimation(int id, int texture_id) {
    foggy::as::Animation &anim = player_anims.getOrLoad(id);
    anim.addFrame(&foggy::Resource::instance().textures.get(texture_id));
}
