#include <Entity.hpp>

namespace foggy {

Entity::Entity(const sf::Vector2f &pos, b2BodyType type) : m_b2_type(type) {
    setPosition(pos);
}

}  // namespace foggy
