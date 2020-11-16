
#include "CircleEntity.hpp"

namespace foggy {

CircleEntity::CircleEntity(const sf::Vector2f &pos, float radius,
                           b2BodyType type)
    : Entity(std::make_unique<sf::CircleShape>(radius), type) {
    GetShape()->setOrigin(radius, radius);
    GetShape()->setPosition(pos);
}

}  // namespace foggy
