#include <SFML/Graphics/RectangleShape.hpp>

#include "RectangleEntity.hpp"

namespace foggy {

RectangleEntity::RectangleEntity(const sf::Vector2f &pos,
                                 const sf::Vector2f &size, b2BodyType type,
                                 const sf::Time &life_time)
    : Entity(std::make_unique<sf::RectangleShape>(size), type, life_time) {
    GetShape()->setOrigin(size.x / 2, size.y / 2);
    GetShape()->setPosition(pos);
}

}  // namespace foggy
