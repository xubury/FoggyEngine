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
    player_inputs.Map(PlayerInput::Down_Realeased,
                      foggy::Action(sf::Keyboard::S, foggy::Action::Released));
    player_inputs.Map(PlayerInput::Right, foggy::Action(sf::Keyboard::D));
    player_inputs.Map(PlayerInput::Left, foggy::Action(sf::Keyboard::A));
    player_inputs.Map(PlayerInput::Attack, foggy::Action(sf::Keyboard::J));
}

void Configuration::InitializePlayerAnims() {
    player_anims
        .Load(PlayerAnim::Idle, &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(0, 3, 7, 16, 35, 0);
    player_anims
        .Load(PlayerAnim::Stand, &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(4, 5, 7, 16, 35, 0);
    player_anims
        .Load(PlayerAnim::Suqat, &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(6, 7, 7, 16, 35, 0);
    player_anims
        .Load(PlayerAnim::Run, &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(8, 13, 7, 16, 35, 0);
    player_anims
        .Load(PlayerAnim::Swoard_Attack_0,
              &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(42, 48, 7, 16, 35, 0);
    player_anims
        .Load(PlayerAnim::Swoard_Attack_1,
              &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(49, 52, 7, 16, 35, 0);
    player_anims
        .Load(PlayerAnim::Swoard_Attack_2,
              &textures.Get(Textures::PlayerAnim_Sheet))
        .AddFrameSheet(53, 58, 7, 16, 35, 0);
}
