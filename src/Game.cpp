
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "util/converter.hpp"

namespace foggy {

Game::Game(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title), m_world(b2Vec2(0, 9.8f)) {}

void Game::Run(int min_fps) {
    m_bodies.emplace_back(
        CreateBody(m_world, 600, 300, 800, 20, b2_staticBody));

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

Game::~Game() {
    for (b2Body *body : m_bodies) {
        delete static_cast<sf::RectangleShape *>(body->GetUserData());
        m_world.DestroyBody(body);
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int x = sf::Mouse::getPosition(m_window).x;
            int y = sf::Mouse::getPosition(m_window).y;

            m_bodies.emplace_back(CreateBody(m_world, x, y, 20, 30));
        }
    }
}

void Game::Update(sf::Time &time) { m_world.Step(time.asSeconds(), 8, 3); }

void Game::Render() {
    m_window.clear();

    for (b2Body *body = m_world.GetBodyList(); body != nullptr;
         body = body->GetNext()) {
        sf::Shape *shape = static_cast<sf::Shape *>(body->GetUserData());
        shape->setPosition(converter::MetersToPixels(body->GetPosition().x),
                           converter::MetersToPixels(body->GetPosition().y));
        shape->setRotation(converter::RadToDeg<double>(body->GetAngle()));
        m_window.draw(*shape);
    }
    m_window.display();
}
b2Body *Game::CreateBody(b2World &world, int pos_x, int pos_y, int size_x,
                         int size_y, b2BodyType type) {
    b2BodyDef body_def;
    body_def.position.Set(converter::PixelsToMeters<double>(pos_x),
                          converter::PixelsToMeters<double>(pos_y));
    body_def.type = type;
    b2PolygonShape b2_shape;
    b2_shape.SetAsBox(converter::PixelsToMeters<double>(size_x / 2.0),
                      converter::PixelsToMeters<double>(size_y / 2.0));

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.4;
    fixture_def.restitution = 0.5;
    fixture_def.shape = &b2_shape;

    b2Body *res = world.CreateBody(&body_def);
    res->CreateFixture(&fixture_def);

    sf::Shape *shape = new sf::RectangleShape(sf::Vector2f(size_x, size_y));
    shape->setOrigin(size_x / 2.0, size_y / 2.0);
    shape->setPosition(pos_x, pos_y);
    if (type == b2_dynamicBody) {
        shape->setFillColor(sf::Color::Blue);
    } else {
        shape->setFillColor(sf::Color::White);
    }
    res->SetUserData(shape);
    return res;
}

} /* namespace foggy */
