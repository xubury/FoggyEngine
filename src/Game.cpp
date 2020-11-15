
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "RectangleEntity.hpp"
#include "util/converter.hpp"

namespace foggy {

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      m_world(sf::Vector2f(0, 9.8f)) {}

void Game::Run(int min_fps) {
    sf::Clock clock;
    m_time_since_last_update = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / min_fps);

    while (m_window.isOpen()) {
        ProcessEvent();

        m_time_since_last_update = clock.restart();
        while (m_time_since_last_update > time_per_frame) {
            m_time_since_last_update -= time_per_frame;
            Update(time_per_frame);
        }
        Update(m_time_since_last_update);
        Render();
    }
}

Game::~Game() {}

void Game::ProcessEvent() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                m_window.close();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int x = sf::Mouse::getPosition(m_window).x;
            int y = sf::Mouse::getPosition(m_window).y;
            m_world.SpawnEntity(RectangleEntity::Create(
                sf::Vector2f(x, y), sf::Vector2f(30, 60), b2_dynamicBody));
            ;
        }
    }
}

void Game::Update(sf::Time &time) { m_world.Step(time.asSeconds(), 8, 3); }

void Game::Render() {
    m_window.clear();

    m_world.RenderOn(m_window);

    m_window.display();
}

} /* namespace foggy */
