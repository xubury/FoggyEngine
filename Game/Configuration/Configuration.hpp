#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics/Font.hpp>

#include "ActionSystem/ActionMap.hpp"
#include "Lua/utils.hpp"
#include "ResourceManager/ResourceManager.hpp"

class Configuration {
   public:
    Configuration() = delete;
    Configuration(const Configuration &) = delete;
    Configuration &operator=(const Configuration &) = delete;

    static void Initialize();

    enum PlayerInput : int { Up, Down, Down_Realeased, Left, Right, Attack };

    static foggy::ActionMap<int> player_inputs;

    enum FontType : int { GUI, Fira };
    static foggy::ResourceManager<sf::Font, FontType> fonts;

    enum PlayerAnim : int {
        Idle,
        Run,
        Stand,
        Suqat,
        Swoard_Attack_0,
        Swoard_Attack_1,
        Swoard_Attack_2
    };

    static foggy::ResourceManager<foggy::as::Animation, PlayerAnim>
        player_anims;

    enum Textures : int {
        PlayerAnim_Sheet,
    };

    static foggy::ResourceManager<sf::Texture, Textures> textures;

   private:
    static void InitializePlayerInputs();
    static void InitializePlayerAnims();

    static int lua_LoadTexture(lua_State *L);
    static int lua_LoadFont(lua_State *L);
};

#endif /* CONFIGURATION_H */
