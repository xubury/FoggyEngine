#ifndef PLAYER_H
#define PLAYER_H

#include "EntitySystem/Entities/Entity.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

class Player : public foggy::es::DefaultEntity {
   public:
    enum Anim { Idle, Run, Stand, Squat, Attack_Swoard };
    static const sf::Time MIN_TIME_BETWEEN_MOVEMENT;

    Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id,
           foggy::es::CollisionSystem *world);

    void Move(const sf::Vector2f &impulse);

    void OnSuqat();

    void OnStandup();

    void OnAttack();

    void OnAttackFinished();

    virtual void draw(
        sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates::Default) const override;

    bool m_freeze;

   private:
    sf::Clock m_movement_timer;
};

#endif /* PLAYER_H */
