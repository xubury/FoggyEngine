#include <sol/sol.hpp>

#include "Configuration/Configuration.hpp"
#include "ResourceManager/Resource.hpp"

foggy::ActionMap<int> Configuration::player_inputs;
foggy::ResourceManager<foggy::as::Animation, Configuration::PlayerAnim>
    Configuration::player_anims;

foggy::ActionMap<int> Configuration::map_inputs;

void Configuration::init() {
    foggy::Resource::lua.set_function("C_loadAnimation", loadPlayerAnimation);
    foggy::Resource::runSrcipt("res/scripts/Animation.lua");
    foggy::Resource::lua["initAnimation"]();
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
    if (player_anims.count((PlayerAnim)id) == 0) {
        player_anims.load((PlayerAnim)id);
    }
    foggy::as::Animation &anim = player_anims.get((PlayerAnim)id);
    anim.addFrame(&foggy::Resource::textures.get(texture_id));
}
