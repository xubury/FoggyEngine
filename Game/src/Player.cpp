#include <iostream>

#include "Configuration/Configuration.hpp"
#include "Player.hpp"
#include "util/converter.hpp"

Player::Player(const sf::Vector2f &pos)
    : foggy::CircleEntity(pos, 30, foggy::Entity::PERSISTANT),
      foggy::ActionTarget<int>(Configuration::player_inputs) {
    Bind(PlayerInput::Up,
         [this](const sf::Event &) { Move(sf::Vector2f(0, 1)); });
    Bind(PlayerInput::Down,
         [this](const sf::Event &) { Move(sf::Vector2f(0, -1)); });
    Bind(PlayerInput::Left,
         [this](const sf::Event &) { Move(sf::Vector2f(-1, 0)); });
    Bind(PlayerInput::Right,
         [this](const sf::Event &) { Move(sf::Vector2f(1, 0)); });
}

void Player::Move(const sf::Vector2f &impulse) {
    GetB2BodyRef()->ApplyLinearImpulse(
        b2Vec2(foggy::converter::PixelsToMeters(impulse.x),
               foggy::converter::PixelsToMeters(impulse.y)),
        GetB2BodyRef()->GetWorldCenter(), true);
}
