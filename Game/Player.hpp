#ifndef PLAYER_H
#define PLAYER_H

#include "ActionSystem/ActionTarget.hpp"
#include "Configuration/Configuration.hpp"
#include "Entity/CircleEntity.hpp"

class Player : public foggy::CircleEntity,
               public foggy::ActionTarget<Configuration::PlayerInput> {
   public:
    static const sf::Time MIN_TIME_BETWEEN_MOVEMENT;
    Player(const sf::Vector2f &pos);

    void Move(const sf::Vector2f &impulse);

   private:
    sf::Clock m_movement_timer;
};

#endif /* PLAYER_H */
