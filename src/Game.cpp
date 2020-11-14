#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Game.hpp"
namespace foggy {

Game::Game(int width, int height, const std::string &title)
    : m_width(width),
      m_height(height),
      m_window(sf::VideoMode(width, height), title) {}

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
    }
}

void Game::Update(sf::Time &) {
    // do something
}

void Game::Render() {
    m_window.clear();

    m_window.display();
}

} /* namespace foggy */
