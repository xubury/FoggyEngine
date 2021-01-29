#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SFML/Graphics/Font.hpp>

#include "ActionSystem/ActionMap.hpp"
#include "ResourceManager/ResourceManager.hpp"

class Configuration  {
   public:
    Configuration() = delete;
    Configuration(const Configuration &) = delete;
    Configuration &operator=(const Configuration &) = delete;

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

    enum PlayerAnim : int {
        Idle,
        Run,
        Squat,
        Sword_Attack_1,
        Sword_Attack_2,
        Sword_Attack_3
    };

    static foggy::ResourceManager<foggy::as::Animation, PlayerAnim>
        player_anims;

   static void init();
   private:
    static void initializePlayerInputs();

    static void loadPlayerAnimation(int id, int texture_id);
};

#endif /* CONFIGURATION_H */
