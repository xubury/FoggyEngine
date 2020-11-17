
#include "CircleEntity.hpp"

namespace foggy {

CircleEntity::CircleEntity(const sf::Vector2f &pos, float radius,
                           b2BodyType type, const sf::Time &life_time)
    : Entity(std::make_unique<sf::CircleShape>(radius), type, life_time) {
    GetShape()->setOrigin(radius, radius);
    GetShape()->setPosition(pos);
}

}  // namespace foggy
