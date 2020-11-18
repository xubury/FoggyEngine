#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Configuration/Configuration.hpp"
#include "Engine/Entity/CircleEntity.hpp"
#include "Engine/Entity/RectangleEntity.hpp"
#include "Engine/util/converter.hpp"
#include "Game.hpp"

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      m_world(sf::Vector2f(0, -9.8f)),
      m_hud_camera(m_window.getDefaultView()) {
    m_world.GetCamera() = m_window.getDefaultView();
}

void Game::Run(int min_fps) {
    Configuration::Initialize();
    // m_window.setFramerateLimit(120);

    m_fps = sf::Text("FPS: " + std::to_string(GetFps()),
                     Configuration::fonts.Get(Configuration::FontType::GUI));

    sf::Clock clock;
    m_time_since_last_update = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / min_fps);
    m_player = std::make_shared<Player>(sf::Vector2f(500, 40));
    m_world.SpawnCollidableEntity(m_player, b2_dynamicBody);
    m_world.SpawnCollidableEntity(
        foggy::RectangleEntity::Create(sf::Vector2f(500, 20),
                                       sf::Vector2f(1000, 40),
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
                m_world.GetCamera().move(sf::Vector2f(-1, 0));
            }
        } else if (event.type == sf::Event::Resized) {
            // update the view to the new size of the window
            sf::Vector2f pos = m_world.GetCamera().GetPosition();
            sf::FloatRect visibleArea(pos.x, pos.y, event.size.width,
                                      event.size.height);
            m_world.GetCamera().reset(visibleArea);
            m_hud_camera.reset(
                sf::FloatRect(0, 0, event.size.width, event.size.height));
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f pos = m_world.GetCamera().ViewToWorld(
                m_window, sf::Mouse::getPosition(m_window));
            m_world.SpawnCollidableEntity(
                foggy::RectangleEntity::Create(pos, sf::Vector2f(30, 15),
                                               sf::seconds(3)),
                b2_dynamicBody);
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2f pos = m_world.GetCamera().ViewToWorld(
                m_window, sf::Mouse::getPosition(m_window));
            m_world.SpawnCollidableEntity(
                foggy::CircleEntity::Create(pos, 30, sf::seconds(3)),
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

    m_window.draw(m_world);

    m_fps.setString("FPS: " + std::to_string(GetFps()));
    m_window.setView(m_hud_camera);
    m_window.draw(m_fps);

    m_fps_clock.restart();
    m_window.display();
}
