#include "ActionSystem/Action.hpp"

namespace foggy {
Action::Action(const sf::Event::EventType &event) : m_type(Type::Pressed) {
    m_event.type = event;
}

Action::Action(const sf::Keyboard::Key &key, int type) : m_type(type) {
    m_event.key.code = key;
    m_event.type = sf::Event::EventType::KeyPressed;
}

Action::Action(const sf::Mouse::Button &button, int type) : m_type(type) {
    m_event.mouseButton.button = button;
    m_event.type = sf::Event::EventType::MouseButtonPressed;
}

bool Action::operator==(const sf::Event &event) const {
    bool res = false;
    switch (event.type) {
        case sf::Event::EventType::KeyPressed: {
            if (m_type & Type::Pressed &&
                event.type == sf::Event::EventType::KeyPressed) {
                res = event.key.code == m_event.key.code;
            }
            break;
        }
        case sf::Event::EventType::KeyReleased: {
            if (m_type & Type::Released &&
                m_event.type == sf::Event::EventType::KeyPressed) {
                res = event.key.code == m_event.key.code;
            }
            break;
        }
        case sf::Event::EventType::MouseButtonPressed: {
            if (m_type & Type::Pressed &&
                m_event.type == sf::Event::EventType::MouseButtonPressed) {
                res = event.mouseButton.button == m_event.mouseButton.button;
            }
            break;
        }
        case sf::Event::EventType::MouseButtonReleased: {
            if (m_type & Type::Released &&
                m_event.type == sf::Event::EventType::MouseButtonPressed) {
                res = event.mouseButton.button == m_event.mouseButton.button;
            }
            break;
        }
        default:
            break;
    }
    return res;
}

bool Action::operator==(const Action &other) const {
    return m_type == other.m_type && other == m_event;
}

bool Action::test() const {
    bool res = false;
    if (m_event.type == sf::Event::EventType::KeyPressed) {
        if (m_type & Type::Pressed) {
            res = sf::Keyboard::isKeyPressed(m_event.key.code);
        }
    } else if (m_event.type == sf::Event::EventType::MouseButtonPressed) {
        if (m_type & Type::Released) {
            res = sf::Mouse::isButtonPressed(m_event.mouseButton.button);
        }
    }
    return res;
}

}  // namespace foggy
