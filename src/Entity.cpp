#include <Entity.hpp>

namespace foggy {

Entity::Entity(ShapePtr shape, b2BodyType type, const sf::Time &life_time)
    : m_b2_type(type), m_shape(std::move(shape)), m_life_time(life_time) {
    m_spawn_timer.restart();
    m_shape->setFillColor(sf::Color::Transparent);
    m_shape->setOutlineColor(sf::Color::Green);
    m_shape->setOutlineThickness(1.f);
}

}  // namespace foggy
