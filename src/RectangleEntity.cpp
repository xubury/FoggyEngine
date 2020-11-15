#include <SFML/Graphics/RectangleShape.hpp>

#include "RectangleEntity.hpp"

namespace foggy {

RectangleEntity::RectangleEntity(const sf::Vector2f &pos,
                                 const sf::Vector2f &size, b2BodyType type)
    : Entity(pos, type) {
    SetShape(std::make_unique<sf::RectangleShape>(size));
    GetShape()->setOrigin(size.x / 2, size.y / 2);
}

void RectangleEntity::UpdateRenderStatus() {
    GetShape()->setPosition(getPosition());
    GetShape()->setRotation(getRotation());
}

}  // namespace foggy
