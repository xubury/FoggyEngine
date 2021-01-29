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
#include "GUI/Configuration.hpp"
#include "GUI/Layout.hpp"
#include "Game.hpp"
#include "Player/Player.hpp"
#include "TileMap/VMap.hpp"

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      m_player_id(-1),
      m_main_menu(m_window),
      m_layer(new foggy::Layer<foggy::es::DefaultEntity *>("Entity", 2)),
      m_map(foggy::VMap::createMapFromFile("res/map.json")),
      m_viewer(m_window, *m_map, Configuration::map_inputs),
      m_status(MainMenu) {
    m_app.systems.add<foggy::es::CollisionSystem>(0.0, 0.0);
    m_app.systems.add<foggy::es::SkinSystem>();
    m_map->add(m_layer);
}

void Game::run(int min_fps) {
    Configuration::Initialize();
    initGui();
    // m_window.setFramerateLimit(120);

    sf::Clock clock;
    m_time_since_last_update = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / min_fps);

    while (m_window.isOpen()) {
        processEvent();
        processEvents();

        m_time_since_last_update = clock.restart();
        while (m_time_since_last_update > time_per_frame) {
            m_time_since_last_update -= time_per_frame;
            update(time_per_frame);
        }
        update(m_time_since_last_update);
        render();
    }
}

Game::~Game() {}

void Game::processEvent() {
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
            m_viewer.setSize(event.size.width, event.size.height);
        }
        switch (m_status) {
            case Normal: {
                foggy::component::Controller::Handle controller;
                auto view = m_app.entities.getByComponents(controller);
                auto end = view.end();
                for (auto cur = view.begin(); cur != end; ++cur) {
                    controller->processEvent(event);
                }
                m_viewer.processEvent(event);
                break;
            }
            case MainMenu: {
                m_main_menu.processEvent(event);
                break;
            }
        }
    }
}

void Game::processEvents() {
    // processMouseEvents();
    switch (m_status) {
        case Normal: {
            foggy::component::Controller::Handle controller;
            auto view = m_app.entities.getByComponents(controller);
            auto end = view.end();
            for (auto cur = view.begin(); cur != end; ++cur) {
                controller->processEvents();
            }
            m_viewer.processEvents();
            break;
        }
        case MainMenu: {
            m_main_menu.processEvents();
            break;
        }
    }
}

void Game::processMouseEvents() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f pos =
            m_viewer.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        int id = m_app.entities.create();
        m_layer->Add(m_app.entities.getPtr(id));
        b2BodyDef body_def;
        body_def.position.Set(foggy::converter::pixelsToMeters<float>(pos.x),
                              foggy::converter::pixelsToMeters<float>(pos.y));
        body_def.type = b2_dynamicBody;
        foggy::component::Collision::Handle collsion =
            m_app.entities.addComponent<foggy::component::Collision>(id,
                                                                     body_def);

        b2CircleShape b2shape;
        b2shape.m_radius = foggy::converter::pixelsToMeters(15.f);
        b2FixtureDef fixture_def;
        fixture_def.density = 1.0;
        fixture_def.friction = 0.4;
        fixture_def.restitution = 0.5;
        fixture_def.shape = &b2shape;
        collsion->addFixture(fixture_def);
        m_timer.addTimer(sf::seconds(3), [id, this]() {
            m_app.entities.remove(id);
            m_layer->remove(m_app.entities.getPtr(id));
        });
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        sf::Vector2f pos =
            m_viewer.mapPixelToCoords(sf::Mouse::getPosition(m_window));
        int id = m_app.entities.create();
        m_layer->Add(m_app.entities.getPtr(id));
        b2BodyDef body_def;
        body_def.position.Set(foggy::converter::pixelsToMeters<float>(pos.x),
                              foggy::converter::pixelsToMeters<float>(pos.y));
        body_def.type = b2_dynamicBody;
        foggy::component::Collision::Handle collsion =
            m_app.entities.addComponent<foggy::component::Collision>(id,
                                                                     body_def);

        b2PolygonShape b2shape;
        b2shape.SetAsBox(foggy::converter::pixelsToMeters(15.f),
                         foggy::converter::pixelsToMeters(10.f));
        b2FixtureDef fixture_def;
        fixture_def.density = 1.0;
        fixture_def.friction = 0.4;
        fixture_def.restitution = 0.5;
        fixture_def.shape = &b2shape;
        collsion->addFixture(fixture_def);
        m_timer.addTimer(sf::seconds(3), [id, this]() {
            m_app.entities.remove(id);
            m_layer->remove(m_app.entities.getPtr(id));
        });
    }
}

void Game::update(sf::Time &delta_time) {
    if (m_player_id >= 0) {
        auto *player =
            dynamic_cast<Player *>(m_app.entities.getPtr(m_player_id));
        sf::Vector2f pos = player->getPosition() - m_viewer.getPosition();
        m_viewer.move(pos.x, pos.y);
    }
    m_app.update(delta_time);
    m_viewer.update(delta_time);
    m_timer.update();
}

void Game::render() {
    m_window.clear();

    if (m_status == MainMenu) {
        m_window.draw(m_main_menu);
    } else {
        m_viewer.draw();
    }

    m_window.display();
}

void Game::initGui() {
    auto *layout = new foggy::gui::VLayout();
    layout->setSpace(25);
    auto *btn =
        new foggy::gui::TextButton("New", sf::Color::Green, sf::Color::White, 5,
                                   foggy::gui::Configuration::default_fonts.get(
                                       foggy::gui::Configuration::Fonts::GUI),
                                   sf::Color::White);
    btn->onClick = [this](const sf::Event &, foggy::gui::Button &) {
        initWorld();
    };
    layout->add(btn);
    m_main_menu.setLayout(layout);
}

void Game::initWorld() {
    b2BodyDef body_def;
    body_def.position.Set(0, foggy::converter::pixelsToMeters(80));
    body_def.type = b2_staticBody;
    uint32_t id = m_app.entities.create();
    m_layer->Add(m_app.entities.getPtr(id));
    foggy::component::Collision::Handle collsion =
        m_app.entities.addComponent<foggy::component::Collision>(id, body_def);

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

    m_player_id = m_app.entities.create<Player>();
    m_layer->Add(m_app.entities.getPtr(m_player_id));
    m_status = Normal;
}
