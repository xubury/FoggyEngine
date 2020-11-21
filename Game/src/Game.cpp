#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Configuration/Configuration.hpp"
#include "Engine/util/converter.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"
#include "EntitySystem/Systems/SkinSystem.hpp"
#include "Game.hpp"

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title),
      // m_world(sf::Vector2f(0, -9.8f)),
      m_hud_camera(m_window.getDefaultView()) {
    m_cam = m_window.getDefaultView();

    m_app.systems.Add<foggy::system::CollisionSystem>(0, -9.8);
    m_app.systems.Add<foggy::system::SkinSystem>();
}

void Game::Run(int min_fps) {
    Configuration::Initialize();
    // m_window.setFramerateLimit(120);

    m_fps = sf::Text("FPS: " + std::to_string(GetFps()),
                     Configuration::fonts.Get(Configuration::FontType::GUI));

    sf::Clock clock;
    m_time_since_last_update = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / min_fps);
    // m_player = std::make_shared<Player>(sf::Vector2f(0, 0));
    // m_world.GetCamera().TrackEntity(m_player);
    // m_world.SpawnCollidableEntity(m_player, b2_dynamicBody);
    // m_world.SpawnCollidableEntity(
    //     foggy::RectangleEntity::Create(sf::Vector2f(0, -20),
    //                                    sf::Vector2f(1000, 40),
    //                                    foggy::Entity::PERSISTANT),
    //     b2_staticBody);

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
            } else if (event.key.code == sf::Keyboard::G) {
                // m_world.DestroyEntity(m_player);
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

            m_app.entities.AddComponent<foggy::component::Collision>(id);
            m_app.entities.AddComponent<foggy::component::Skin>(
                id, foggy::component::Skin::Circle);
            sf::CircleShape *shape = dynamic_cast<sf::CircleShape *>(
                m_app.entities.Get(id)
                    .Component<foggy::component::Skin>()
                    ->shape.get());
            shape->setOrigin(30, 30);
            shape->setRadius(30);

            b2CircleShape b2shape;
            b2shape.m_radius = foggy::converter::PixelsToMeters(30.f);

            m_app.systems.System<foggy::system::CollisionSystem>()
                ->AddRigidBody(m_app.entities, id, pos, &b2shape,
                               b2_dynamicBody);

        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        } else {
            // m_player->ProcessEvent(event);
        }
    }
    // m_player->ProcessEvents();
}

void Game::Update(sf::Time &delta_time) {
    // m_world.Update(time);
    m_app.Update(delta_time);
}

void Game::Render() {
    m_window.clear();

    m_window.setView(m_cam);

    foggy::component::Skin::Handle skin_handle;
    auto view = m_app.entities.GetByComponents(skin_handle);
    auto end = view.End();
    for (auto cur = view.Begin(); cur != end; ++cur) {
        m_window.draw(**cur);
    }

    m_fps.setString("FPS: " + std::to_string(GetFps()));
    m_window.setView(m_hud_camera);
    m_window.draw(m_fps);

    m_fps_clock.restart();
    m_window.display();
}
