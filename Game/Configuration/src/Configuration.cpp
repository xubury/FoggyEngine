#include "Configuration/Configuration.hpp"

foggy::ResourceManager<sf::Texture, Configuration::Textures>
    Configuration::textures;
foggy::ResourceManager<sf::Font, Configuration::FontType> Configuration::fonts;

foggy::ActionMap<int> Configuration::player_inputs;
foggy::ResourceManager<foggy::as::Animation, Configuration::PlayerAnim>
    Configuration::player_anims;

void Configuration::Initialize() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "_LoadTexture", lua_LoadTexture);
    lua_register(L, "_LoadFont", lua_LoadFont);

    LUA_BEGIN_ENUM_TABLE(L)
    LUA_ENUM_REGISTER(L, Fira)
    LUA_ENUM_REGISTER(L, GUI)
    LUA_END_ENUM_TABLE(L, FontType)

    LUA_BEGIN_ENUM_TABLE(L)
    LUA_ENUM_REGISTER(L, PlayerAnim_Sheet)
    LUA_END_ENUM_TABLE(L, Textures)

    foggy::CheckLua(L, luaL_dofile(L, "../Resources.lua"));
    lua_getglobal(L, "LoadResources");

    if (lua_isfunction(L, -1)) {
        foggy::CheckLua(L, lua_pcall(L, 0, 0, 0));
    }
    lua_pop(L, 1);

    InitializePlayerInputs();
    InitializePlayerAnims();
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

int Configuration::lua_LoadTexture(lua_State *L) {
    if (lua_gettop(L) != 2) return -1;
    int id = lua_tointeger(L, 1);
    std::string filename = lua_tostring(L, 2);
    textures.Load((Textures)id, filename);
    return 0;
}

int Configuration::lua_LoadFont(lua_State *L) {
    if (lua_gettop(L) != 2) return -1;
    int id = lua_tointeger(L, 1);
    std::string filename = lua_tostring(L, 2);
    fonts.Load((FontType)id, filename);
    return 0;
}
