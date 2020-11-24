#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics/Font.hpp>

#include "ActionSystem/ActionMap.hpp"
#include "ResourceManager/ResourceManager.hpp"

class Configuration {
   public:
    Configuration() = delete;
    Configuration(const Configuration &) = delete;
    Configuration &operator=(const Configuration &) = delete;

    static void Initialize();

    enum PlayerInput : int { Up, Down, Down_Realeased, Left, Right, Attack };

    static foggy::ActionMap<int> player_inputs;

    enum FontType : int { GUI };
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
        PlayerAnim_Idle0,
        PlayerAnim_Idle1,
        PlayerAnim_Idle2,
        PlayerAnim_Idle3,
    };
    static foggy::ResourceManager<sf::Texture, Textures> textures;

   private:
    static void InitializeFonts();
    static void InitializeTextures();
    static void InitializePlayerInputs();
    static void InitializePlayerAnims();
};

#endif /* CONFIGURATION_H */
