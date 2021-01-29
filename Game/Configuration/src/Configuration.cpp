#include <sol/sol.hpp>

#include "Configuration/Configuration.hpp"

foggy::ResourceManager<sf::Texture, Configuration::Textures>
    Configuration::textures;
foggy::ResourceManager<sf::Font, Configuration::FontType> Configuration::fonts;

foggy::ActionMap<int> Configuration::player_inputs;
foggy::ResourceManager<foggy::as::Animation, Configuration::PlayerAnim>
    Configuration::player_anims;

foggy::ActionMap<int> Configuration::map_inputs;

void Configuration::initialize() {
    sol::state lua;

    lua.set_function("C_loadFont", loadFont);
    lua.set_function("C_loadTexture", loadTexture);
    lua.set_function("C_loadAnimation", loadPlayerAnimation);

    auto res = lua.safe_script_file("res/scripts/Resources.lua");
    if (!res.valid()) {
        sol::error err = res;
        std::cout << err.what() << std::endl;
        return;
    }
    lua["LoadResources"]();

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

void Configuration::loadTexture(int id, const std::string &filename) {
    textures.load((Textures)id, filename);
}

void Configuration::loadFont(int id, const std::string &filename) {
    fonts.load((FontType)id, filename);
}

void Configuration::loadPlayerAnimation(int id, int texture_id) {
    if (player_anims.count((PlayerAnim)id) == 0) {
        player_anims.load((PlayerAnim)id);
    }
    foggy::as::Animation &anim = player_anims.get((PlayerAnim)id);
    anim.addFrame(&textures.get((Textures)texture_id));
}
