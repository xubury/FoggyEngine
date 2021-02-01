#include "Configuration/Configuration.hpp"

#include <sol/sol.hpp>

#include "ResourceManager/Resource.hpp"

foggy::ActionMap<int> Configuration::player_inputs;

foggy::ActionMap<int> Configuration::map_inputs;

Configuration::__Initializer Configuration::__initializer__;

void Configuration::init() { initializePlayerInputs(); }

void Configuration::initializePlayerInputs() {
    player_inputs.map(PlayerInput::Up, foggy::Action(sf::Keyboard::W));
    player_inputs.map(PlayerInput::Down, foggy::Action(sf::Keyboard::S));
    player_inputs.map(PlayerInput::Down_Realeased,
                      foggy::Action(sf::Keyboard::S, foggy::Action::Released));
    player_inputs.map(PlayerInput::Right, foggy::Action(sf::Keyboard::D));
    player_inputs.map(PlayerInput::Left, foggy::Action(sf::Keyboard::A));
    player_inputs.map(PlayerInput::Attack, foggy::Action(sf::Keyboard::J));
}
