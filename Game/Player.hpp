#ifndef PLAYER_H
#define PLAYER_H

#include "EntitySystem/Entities/Entity.hpp"

class Player : public foggy::es::DefaultEntity {
   public:
    static const sf::Time MIN_TIME_BETWEEN_MOVEMENT;
    Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id);

    void Move(const sf::Vector2f &impulse);

   private:
    sf::Clock m_movement_timer;
};

#endif /* PLAYER_H */
