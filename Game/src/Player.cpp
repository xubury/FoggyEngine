#include <iostream>

#include "Configuration/Configuration.hpp"
#include "Player.hpp"
#include "util/converter.hpp"

const sf::Time Player::MIN_TIME_BETWEEN_MOVEMENT = sf::milliseconds(10);

Player::Player(const sf::Vector2f &pos)
    : foggy::CircleEntity(pos, 15, foggy::Entity::PERSISTANT),
      foggy::ActionTarget<Configuration::PlayerInput>(
          Configuration::player_inputs) {
    Bind(Configuration::PlayerInput::Up,
         [this](const sf::Event &) { Move(sf::Vector2f(0, 10)); });
    Bind(Configuration::PlayerInput::Down,
         [this](const sf::Event &) { Move(sf::Vector2f(0, -10)); });
    Bind(Configuration::PlayerInput::Left,
         [this](const sf::Event &) { Move(sf::Vector2f(-10, 0)); });
    Bind(Configuration::PlayerInput::Right,
         [this](const sf::Event &) { Move(sf::Vector2f(10, 0)); });
}

void Player::Move(const sf::Vector2f &impulse) {
    /* Limit the movement frequncy. Otherwise, the FPS will have huge effect on
     * player movement */
    if (m_movement_timer.getElapsedTime() < MIN_TIME_BETWEEN_MOVEMENT) {
        return;
    }
    GetB2BodyRef()->ApplyLinearImpulse(
        b2Vec2(foggy::converter::PixelsToMeters<float>(impulse.x),
               foggy::converter::PixelsToMeters<float>(impulse.y)),
        GetB2BodyRef()->GetWorldCenter(), true);
    m_movement_timer.restart();
}
