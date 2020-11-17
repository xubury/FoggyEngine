
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Engine/Entity/CircleEntity.hpp"
#include "Engine/Entity/RectangleEntity.hpp"
#include "Engine/util/converter.hpp"
#include "Game.hpp"

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      m_world(sf::Vector2f(0, -9.8f)) {}

void Game::Run(int min_fps) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Load font failed" << std::endl;
    }
    m_fps = sf::Text("FPS: " + std::to_string(GetFps()), font);

    sf::Clock clock;
    m_time_since_last_update = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / min_fps);
    m_player = std::make_shared<Player>(sf::Vector2f(500, 40));
    m_world.SpawnEntity(m_player);
    m_world.SpawnEntity(foggy::RectangleEntity::Create(
        sf::Vector2f(500, 20), sf::Vector2f(1000, 40), b2_staticBody,
        foggy::Entity::PERSISTANT));

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
            int y = m_window.getSize().y - sf::Mouse::getPosition(m_window).y;
            m_world.SpawnEntity(foggy::RectangleEntity::Create(
                sf::Vector2f(x, y), sf::Vector2f(30, 15), b2_dynamicBody,
                sf::seconds(3)));
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            int x = sf::Mouse::getPosition(m_window).x;
            int y = m_window.getSize().y - sf::Mouse::getPosition(m_window).y;
            m_world.SpawnEntity(foggy::CircleEntity::Create(
                sf::Vector2f(x, y), 30, b2_dynamicBody, sf::seconds(3)));
        } else {
            m_player->ProcessEvent(event);
        }
    }
    m_player->ProcessEvents();
}

void Game::Update(sf::Time &time) { m_world.Update(time); }

void Game::Render() {
    m_window.clear();
    m_world.RenderOn(m_window);

    m_fps.setString("FPS: " + std::to_string(GetFps()));
    m_window.draw(m_fps);
    m_window.display();
    m_fps_clock.restart();
}
