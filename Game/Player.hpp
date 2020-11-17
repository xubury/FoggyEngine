#ifndef PLAYER_H
#define PLAYER_H

#include "ActionSystem/ActionTarget.hpp"
#include "Entity/CircleEntity.hpp"

class Player : public foggy::CircleEntity, public foggy::ActionTarget<int> {
   public:
    enum PlayerInput : int { Up, Down, Left, Right };

   public:
    static foggy::ActionMap<int> s_player_inputs;

    Player(const sf::Vector2f &pos);

    void Move(const sf::Vector2f &acc);

   private:
};

#endif /* PLAYER_H */
