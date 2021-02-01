#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "EntitySystem/Entities/Entity.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

class Player : public foggy::es::DefaultEntity {
   public:
    Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id);

    virtual void draw(
        sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates::Default) const override;

   private:
    sf::Clock m_movement_timer;
    sf::Clock m_attack_timer;
    bool m_facing_right;
};

#endif /* PLAYER_HPP */
