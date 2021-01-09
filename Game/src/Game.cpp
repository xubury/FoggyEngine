#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Configuration/Configuration.hpp"
#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Controller.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"
#include "EntitySystem/Systems/SkinSystem.hpp"
#include "GUI/Button.hpp"
#include "GUI/Layout.hpp"
#include "Game.hpp"
#include "Player/Player.hpp"

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      // m_world(sf::Vector2f(0, -9.8f)),
      m_hud_camera(m_window.getDefaultView()),
      m_player_id(-1),
      m_main_menu(m_window),
      m_status(MainMenu) {
    m_cam = m_window.getDefaultView();
    m_cam.setSize(width, -height);

    m_app.systems.add<foggy::es::CollisionSystem>(0, -9.8);
    m_app.systems.add<foggy::es::SkinSystem>();
}

void Game::Run(int min_fps) {
    Configuration::Initialize();
    InitGui();
    // m_window.setFramerateLimit(120);

    m_fps = sf::Text("FPS: " + std::to_string(GetFps()),
                     Configuration::fonts.Get(Configuration::FontType::GUI));

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
        } else if (event.type == sf::Event::Resized) {
            // update the view to the new size of the window
            m_cam.setSize(event.size.width, -(int)event.size.height);
            m_hud_camera.reset(
                sf::FloatRect(0, 0, event.size.width, event.size.height));
        }
        switch (m_status) {
            case Normal: {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f pos = m_window.mapPixelToCoords(
                        sf::Mouse::getPosition(m_window), m_cam);
                    int id = m_app.entities.Create();
                    b2BodyDef body_def;
                    body_def.position.Set(
                        foggy::converter::pixelsToMeters<float>(pos.x),
                        foggy::converter::pixelsToMeters<float>(pos.y));
                    body_def.type = b2_dynamicBody;
                    foggy::component::Collision::Handle collsion =
                        m_app.entities
                            .AddComponent<foggy::component::Collision>(
                                id, body_def);

                    b2CircleShape b2shape;
                    b2shape.m_radius = foggy::converter::pixelsToMeters(15.f);
                    b2FixtureDef fixture_def;
                    fixture_def.density = 1.0;
                    fixture_def.friction = 0.4;
                    fixture_def.restitution = 0.5;
                    fixture_def.shape = &b2shape;
                    collsion->addFixture(fixture_def);
                    m_timer.AddTimer(sf::seconds(3), [id, this]() {
                        m_app.entities.Remove(id);
                    });
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    sf::Vector2f pos = m_window.mapPixelToCoords(
                        sf::Mouse::getPosition(m_window), m_cam);
                    int id = m_app.entities.Create();
                    b2BodyDef body_def;
                    body_def.position.Set(
                        foggy::converter::pixelsToMeters<float>(pos.x),
                        foggy::converter::pixelsToMeters<float>(pos.y));
                    body_def.type = b2_dynamicBody;
                    foggy::component::Collision::Handle collsion =
                        m_app.entities
                            .AddComponent<foggy::component::Collision>(
                                id, body_def);

                    b2PolygonShape b2shape;
                    b2shape.SetAsBox(foggy::converter::pixelsToMeters(15.f),
                                     foggy::converter::pixelsToMeters(10.f));
                    b2FixtureDef fixture_def;
                    fixture_def.density = 1.0;
                    fixture_def.friction = 0.4;
                    fixture_def.restitution = 0.5;
                    fixture_def.shape = &b2shape;
                    collsion->addFixture(fixture_def);
                    m_timer.AddTimer(sf::seconds(3), [id, this]() {
                        m_app.entities.Remove(id);
                    });
                } else {
                    foggy::component::Controller::Handle controller;
                    auto view = m_app.entities.GetByComponents(controller);
                    auto end = view.End();
                    for (auto cur = view.Begin(); cur != end; ++cur) {
                        controller->ProcessEvent(event);
                    }
                }
                break;
            }
            case MainMenu: {
                m_main_menu.processEvent(event);
                break;
            }
        }
    }
    switch (m_status) {
        case Normal: {
            foggy::component::Controller::Handle controller;
            auto view = m_app.entities.GetByComponents(controller);
            auto end = view.End();
            for (auto cur = view.Begin(); cur != end; ++cur) {
                controller->ProcessEvents();
            }
            break;
        }
        case MainMenu: {
            m_main_menu.processEvents();
            break;
        }
    }
}

void Game::Update(sf::Time &delta_time) {
    if (m_player_id >= 0) {
        auto *player =
            dynamic_cast<Player *>(m_app.entities.GetPtr(m_player_id));
        sf::Vector2f pos =
            player->component<foggy::component::Transform>()->getPosition() -
            m_cam.getCenter();
        m_cam.move(pos.x, pos.y);
    }
    m_timer.Update();
    m_app.Update(delta_time);
}

void Game::Render() {
    m_window.clear();

    m_window.setView(m_cam);
    auto iter = m_app.entities.Begin();
    auto end = m_app.entities.End();
    for (; iter != end; ++iter) {
        m_window.draw(m_app.entities.Get(*iter));
    }
    m_fps.setString("FPS: " + std::to_string(GetFps()));
    m_window.setView(m_hud_camera);
    m_window.draw(m_fps);

    if (m_status == MainMenu) {
        m_window.draw(m_main_menu);
    }

    m_fps_clock.restart();
    m_window.display();
}

void Game::InitGui() {
    auto *layout = new foggy::VLayout();
    layout->setSpace(25);
    auto *btn = new foggy::TextButton(
        "New", sf::Color::Green, sf::Color::White, 5,
        Configuration::fonts.Get(Configuration::GUI), sf::Color::White);
    btn->onClick = [this](const sf::Event &, foggy::Button &) { InitWorld(); };
    layout->add(btn);
    m_main_menu.setLayout(layout);
}

void Game::InitWorld() {
    b2BodyDef body_def;
    body_def.position.Set(0, foggy::converter::pixelsToMeters(-80));
    body_def.type = b2_staticBody;
    uint32_t id = m_app.entities.Create();
    foggy::component::Collision::Handle collsion =
        m_app.entities.AddComponent<foggy::component::Collision>(id, body_def);

    float width = 800;
    float height = 20;
    b2PolygonShape b2polygon_shape;
    b2polygon_shape.SetAsBox(foggy::converter::pixelsToMeters(width / 2),
                             foggy::converter::pixelsToMeters(height / 2));
    b2FixtureDef fixture;
    fixture.density = 1.0;
    fixture.friction = 1.0;
    fixture.restitution = 0;
    fixture.shape = &b2polygon_shape;
    collsion->addFixture(fixture);

    m_player_id = m_app.entities.Create<Player>();
    m_status = Normal;
}
