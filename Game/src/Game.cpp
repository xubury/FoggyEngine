#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Engine/Entity/CircleEntity.hpp"
#include "Engine/Entity/RectangleEntity.hpp"
#include "Engine/util/converter.hpp"
#include "Game.hpp"

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      m_world(sf::Vector2f(0, -9.8f)),
      m_camera(m_window.getDefaultView()),
      m_hud_camera(m_window.getDefaultView()) {}

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
    m_world.SpawnEntity(m_player, b2_dynamicBody);
    m_world.SpawnEntity(foggy::RectangleEntity::Create(
                            sf::Vector2f(500, 20), sf::Vector2f(1000, 40),
                            foggy::Entity::PERSISTANT),
                        b2_staticBody);

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
            if (event.key.code == sf::Keyboard::Left) {
                m_camera.move(sf::Vector2f(-1, 0));
            }
        } else if (event.type == sf::Event::Resized) {
            // update the view to the new size of the window
            sf::Vector2f center =
                m_camera.getCenter() - sf::Vector2f(m_camera.getSize().x / 2,
                                                    m_camera.getSize().y / 2);
            sf::FloatRect visibleArea(center.x, center.y, event.size.width,
                                      event.size.height);
            m_camera.reset(visibleArea);
            m_hud_camera.reset(
                sf::FloatRect(0, 0, event.size.width, event.size.height));
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int x = sf::Mouse::getPosition(m_window).x;
            int y = m_window.getSize().y - sf::Mouse::getPosition(m_window).y;
            m_world.SpawnEntity(
                foggy::RectangleEntity::Create(
                    sf::Vector2f(x, y), sf::Vector2f(30, 15), sf::seconds(3)),
                b2_dynamicBody);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            int x = sf::Mouse::getPosition(m_window).x;
            int y = m_window.getSize().y - sf::Mouse::getPosition(m_window).y;
            m_world.SpawnEntity(foggy::CircleEntity::Create(sf::Vector2f(x, y),
                                                            30, sf::seconds(3)),
                                b2_dynamicBody);
        } else {
            m_player->ProcessEvent(event);
        }
    }
    m_player->ProcessEvents();
}

void Game::Update(sf::Time &time) { m_world.Update(time); }

void Game::Render() {
    m_window.clear();
    m_fps.setString("FPS: " + std::to_string(GetFps()));

    m_window.setView(m_hud_camera);
    m_window.draw(m_fps);

    m_window.setView(m_camera);
    m_world.RenderOn(m_window);

    m_window.display();
    m_fps_clock.restart();
}
