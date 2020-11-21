#include "Configuration/Configuration.hpp"

foggy::ActionMap<int> Configuration::player_inputs;
foggy::ResourceManager<sf::Font, Configuration::FontType> Configuration::fonts;

void Configuration::Initialize() {
    InitializePlayerInputs();
    InitializeFonts();
}

void Configuration::InitializePlayerInputs() {
    player_inputs.Map(PlayerInput::Up, foggy::Action(sf::Keyboard::W));
    player_inputs.Map(PlayerInput::Down, foggy::Action(sf::Keyboard::S));
    player_inputs.Map(PlayerInput::Right, foggy::Action(sf::Keyboard::D));
    player_inputs.Map(PlayerInput::Left, foggy::Action(sf::Keyboard::A));
}

void Configuration::InitializeFonts() {
    fonts.Load(FontType::GUI, "arial.ttf");
}
