#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <SFML/Graphics/Font.hpp>

#include "ActionSystem/ActionMap.hpp"
#include "ResourceManager/Resource.hpp"
#include "ResourceManager/ResourceManager.hpp"

class Configuration {
   public:
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

    static void init();

   private:
    static void initializePlayerInputs();

    static struct __Initializer {
        __Initializer() { Configuration::init(); };
    } __initializer__;
};

#endif /* CONFIGURATION_HPP */
