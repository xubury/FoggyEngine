#include <sol/sol.hpp>

#include "Configuration/Configuration.hpp"

foggy::ResourceManager<sf::Texture, Configuration::Textures>
    Configuration::textures;
foggy::ResourceManager<sf::Font, Configuration::FontType> Configuration::fonts;

foggy::ActionMap<int> Configuration::player_inputs;
foggy::ResourceManager<foggy::as::Animation, Configuration::PlayerAnim>
    Configuration::player_anims;

void Configuration::Initialize() {
    sol::state lua;

    lua.open_libraries();
    lua["Textures"] =
        lua.create_table_with("PlayerAnim_Sheet", PlayerAnim_Sheet);
    lua["FontType"] = lua.create_table_with("GUI", GUI, "Fira", Fira);

    lua["PlayerAnim"] = lua.create_table_with(
        "Idle", Idle, "Run", Run, "Stand", Stand, "Squat", Squat,
        "Swoard_Attack_0", Swoard_Attack_0, "Swoard_Attack_1", Swoard_Attack_1,
        "Swoard_Attack_2", Swoard_Attack_2);

    lua.set_function("C_LoadFont", LoadFont);
    lua.set_function("C_LoadTexture", LoadTexture);
    lua.set_function("C_LoadAnimation", LoadPlayerAnimation);

    lua.script_file("../Resources.lua");
    lua["LoadResources"]();

    InitializePlayerInputs();
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

void Configuration::LoadTexture(int id, const std::string &filename) {
    textures.Load((Textures)id, filename);
}

void Configuration::LoadFont(int id, const std::string &filename) {
    fonts.Load((FontType)id, filename);
}

void Configuration::LoadPlayerAnimation(int id, int texture_id, int start_frame,
                                        int end_frame, int cols, int rows) {
    player_anims.Load((PlayerAnim)id, &textures.Get((Textures)texture_id))
        .AddFrameSheet(start_frame, end_frame, cols, rows, 35,
                       0);  // TODO: remove the offset by editing the sheet?
}
