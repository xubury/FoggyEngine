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

    enum class PlayerInput { Up, Down, Left, Right };

    static foggy::ActionMap<PlayerInput> player_inputs;

    enum class FontType { GUI };
    static foggy::ResourceManager<sf::Font, FontType> fonts;

   private:
    static void InitializePlayerInputs();
    static void InitializeFonts();
};

#endif /* CONFIGURATION_H */