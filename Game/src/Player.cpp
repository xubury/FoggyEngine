#include <iostream>

#include "Player.hpp"

foggy::ActionMap<int> Player::s_player_inputs;

Player::Player(const sf::Vector2f &pos)
    : foggy::CircleEntity(pos, 30, b2_dynamicBody, foggy::Entity::PERSISTANT),
      foggy::ActionTarget<int>(s_player_inputs) {
    s_player_inputs.Map(PlayerInput::Up, foggy::Action(sf::Keyboard::W));
    s_player_inputs.Map(PlayerInput::Down, foggy::Action(sf::Keyboard::S));
    s_player_inputs.Map(PlayerInput::Right, foggy::Action(sf::Keyboard::D));
    s_player_inputs.Map(PlayerInput::Left, foggy::Action(sf::Keyboard::A));

    Bind(PlayerInput::Up,
         [this](const sf::Event &) { Move(sf::Vector2f(0, -20)); });
    Bind(PlayerInput::Down,
         [this](const sf::Event &) { Move(sf::Vector2f(0, 20)); });
    Bind(PlayerInput::Left,
         [this](const sf::Event &) { Move(sf::Vector2f(-20, 0)); });
    Bind(PlayerInput::Right,
         [this](const sf::Event &) { Move(sf::Vector2f(20, 0)); });
}

void Player::Move(const sf::Vector2f &acc) {
    float mass = GetB2BodyRef()->GetMass();
    GetB2BodyRef()->ApplyForce(b2Vec2(acc.x * mass, acc.y * mass),
                               GetB2BodyRef()->GetWorldCenter(), true);
}
