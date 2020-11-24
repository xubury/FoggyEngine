#include "Configuration/Configuration.hpp"

foggy::ResourceManager<sf::Texture, Configuration::Textures>
    Configuration::textures;
foggy::ResourceManager<sf::Font, Configuration::FontType> Configuration::fonts;

foggy::ActionMap<int> Configuration::player_inputs;
foggy::ResourceManager<foggy::as::Animation, Configuration::PlayerAnim>
    Configuration::player_anims;

void Configuration::Initialize() {
    InitializeFonts();
    InitializeTextures();

    InitializePlayerInputs();
    InitializePlayerAnims();
}

void Configuration::InitializeTextures() {
    textures.Load(Textures::PlayerAnim_Sheet, "adventurer-v1.5-Sheet.png");
}

void Configuration::InitializeFonts() {
    fonts.Load(FontType::GUI, "arial.ttf");
}
void Configuration::InitializePlayerInputs() {
    player_inputs.Map(PlayerInput::Up, foggy::Action(sf::Keyboard::W));
    player_inputs.Map(PlayerInput::Down, foggy::Action(sf::Keyboard::S));
    player_inputs.Map(PlayerInput::Right, foggy::Action(sf::Keyboard::D));
    player_inputs.Map(PlayerInput::Left, foggy::Action(sf::Keyboard::A));
}

void Configuration::InitializePlayerAnims() {
    player_anims
        .Load(PlayerAnim::Stand, &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(0, 4, 7, 16, 35, 0);
    player_anims
        .Load(PlayerAnim::Run, &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(8, 13, 7, 16, 35, 0);
}
