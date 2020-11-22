#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Configuration/Configuration.hpp"
#include "Engine/util/converter.hpp"
#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Controller.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"
#include "EntitySystem/Systems/SkinSystem.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "TimerSystem/TimerSystem.hpp"

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      // m_world(sf::Vector2f(0, -9.8f)),
      m_hud_camera(m_window.getDefaultView()) {
    m_cam = m_window.getDefaultView();

    m_app.systems.Add<foggy::es::CollisionSystem>(0, -9.8);
    m_app.systems.Add<foggy::es::SkinSystem>();
}

void Game::Run(int min_fps) {
    Configuration::Initialize();
    // m_window.setFramerateLimit(120);

    uint32_t id = m_app.entities.Create<Player>();
    Player *player = dynamic_cast<Player *>(m_app.entities.GetPtr(id));

    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    m_app.entities.AddComponent<foggy::component::Collision>(
        id, m_app.systems.System<foggy::es::CollisionSystem>(), body_def);

    b2CircleShape b2shape;
    b2shape.m_radius = foggy::converter::PixelsToMeters(30.f);
    b2FixtureDef fixture_def;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.4;
    fixture_def.restitution = 0.5;
    fixture_def.shape = &b2shape;
    player->Component<foggy::component::Collision>()->AddFixture(fixture_def);

    m_app.entities.AddComponent<foggy::component::Controller>(
        id, Configuration::player_inputs);
    foggy::component::Controller::Handle handle =
        m_app.entities.GetComponent<foggy::component::Controller>(id);
    handle->Bind(Configuration::PlayerInput::Up, [player](const sf::Event &) {
        player->Move(sf::Vector2f(0, 10));
    });
    handle->Bind(Configuration::PlayerInput::Down, [player](const sf::Event &) {
        player->Move(sf::Vector2f(0, -10));
    });
    handle->Bind(Configuration::PlayerInput::Left, [player](const sf::Event &) {
        player->Move(sf::Vector2f(-10, 0));
    });
    handle->Bind(
        Configuration::PlayerInput::Right,
        [player](const sf::Event &) { player->Move(sf::Vector2f(10, 0)); });

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
            m_cam.Resize(event.size.width, event.size.height);
            m_hud_camera.reset(
                sf::FloatRect(0, 0, event.size.width, event.size.height));
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f pos =
                m_cam.ViewToWorld(m_window, sf::Mouse::getPosition(m_window));
            int id = m_app.entities.Create();
            foggy::es::DefaultEntity &entity = m_app.entities.Get(id);

            m_app.entities.AddComponent<foggy::component::Skin>(
                id, foggy::component::Skin::Circle);
            sf::CircleShape *shape = dynamic_cast<sf::CircleShape *>(
                entity.Component<foggy::component::Skin>()->shape.get());
            shape->setOrigin(30, 30);
            shape->setRadius(30);

            b2BodyDef body_def;
            body_def.position.Set(
                foggy::converter::PixelsToMeters<float>(pos.x),
                foggy::converter::PixelsToMeters<float>(pos.y));
            body_def.type = b2_dynamicBody;
            m_app.entities.AddComponent<foggy::component::Collision>(
                id, m_app.systems.System<foggy::es::CollisionSystem>(),
                body_def);

            b2CircleShape b2shape;
            b2shape.m_radius = foggy::converter::PixelsToMeters(30.f);
            b2FixtureDef fixture_def;
            fixture_def.density = 1.0;
            fixture_def.friction = 0.4;
            fixture_def.restitution = 0.5;
            fixture_def.shape = &b2shape;
            entity.Component<foggy::component::Collision>()->AddFixture(
                fixture_def);
            m_timer.AddTimer(sf::seconds(1),
                             [id, this]() { m_app.entities.Remove(id); });
        } else {
            foggy::component::Controller::Handle c_handle;
            auto view = m_app.entities.GetByComponents(c_handle);
            auto end = view.End();
            for (auto cur = view.Begin(); cur != end; ++cur) {
                cur->Component<foggy::component::Controller>()->ProcessEvent(
                    event);
            }
        }
    }
    foggy::component::Controller::Handle c_handle;
    auto view = m_app.entities.GetByComponents(c_handle);
    auto end = view.End();
    for (auto cur = view.Begin(); cur != end; ++cur) {
        cur->Component<foggy::component::Controller>()->ProcessEvents();
    }
}

void Game::Update(sf::Time &delta_time) {
    m_timer.Update();
    m_app.Update(delta_time);
}

void Game::Render() {
    m_window.clear();

    m_window.setView(m_cam);

    foggy::component::Skin::Handle skin_handle;
    auto view = m_app.entities.GetByComponents(skin_handle);
    auto end = view.End();
    for (auto cur = view.Begin(); cur != end; ++cur) {
        cur->draw(m_window);
    }

    m_fps.setString("FPS: " + std::to_string(GetFps()));
    m_window.setView(m_hud_camera);
    m_window.draw(m_fps);

    m_fps_clock.restart();
    m_window.display();
}
