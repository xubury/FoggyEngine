#include <iostream>

#include "Configuration/Configuration.hpp"
#include "Engine/EntitySystem/Components/Collision.hpp"
#include "Player.hpp"
#include "util/converter.hpp"
const sf::Time Player::MIN_TIME_BETWEEN_MOVEMENT = sf::milliseconds(10);

Player::Player(foggy::es::EntityManager<DefaultEntity> *manager, uint32_t id)
    : foggy::es::DefaultEntity(manager, id) {}

void Player::Move(const sf::Vector2f &impulse) {
    /* Limit the movement frequncy. Otherwise, the FPS will have huge effect on
     * player movement */
    if (m_movement_timer.getElapsedTime() < MIN_TIME_BETWEEN_MOVEMENT) {
        return;
    }
    b2Body *b2body_ref = Component<foggy::component::Collision>()->b2body_ref;
    b2body_ref->ApplyLinearImpulse(
        b2Vec2(foggy::converter::PixelsToMeters<float>(impulse.x),
               foggy::converter::PixelsToMeters<float>(impulse.y)),
        b2body_ref->GetWorldCenter(), true);
    m_movement_timer.restart();
}
