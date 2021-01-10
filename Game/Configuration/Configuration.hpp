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

    enum MapInputs {
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight,
        TakeScreen,
    };

    static foggy::ActionMap<int> map_inputs;

    enum FontType : int { GUI, Fira };
    static foggy::ResourceManager<sf::Font, FontType> fonts;

    enum PlayerAnim : int {
        Idle,
        Run,
        Stand,
        Squat,
        Sword_Attack_0,
        Sword_Attack_1,
        Sword_Attack_2
    };

    static foggy::ResourceManager<foggy::as::Animation, PlayerAnim>
        player_anims;

    enum Textures : int {
        PlayerAnim_Sheet,
    };

    static foggy::ResourceManager<sf::Texture, Textures> textures;

   private:
    static void InitializePlayerInputs();

    static void LoadTexture(int id, const std::string &name);
    static void LoadFont(int id, const std::string &name);
    static void LoadPlayerAnimation(int id, int texture_id, int start_frame,
                                    int end_frame, int cols, int rows);
};

#endif /* CONFIGURATION_H */
