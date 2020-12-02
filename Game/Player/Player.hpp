#ifndef PLAYER_H
#define PLAYER_H

#include "EntitySystem/Entities/Entity.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

class Player : public foggy::es::DefaultEntity {
   public:
    static const sf::Time MIN_TIME_BETWEEN_MOVEMENT;
    static const sf::Time MIN_TIME_BETWEEN_ATTACK;

    Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id);

    void Move(const sf::Vector2f &impulse);

    virtual void draw(
        sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates::Default) const override;

    void Squat();
    void Standup();
    void Attack();

   private:
    sf::Clock m_movement_timer;
    sf::Clock m_attack_timer;
    bool m_facing_right;
};

#endif /* PLAYER_H */
