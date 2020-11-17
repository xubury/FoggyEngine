
#include "Entity/CircleEntity.hpp"
#include "util/converter.hpp"

namespace foggy {

CircleEntity::CircleEntity(const sf::Vector2f &pos, float radius,
                           const sf::Time &life_time)
    : Entity(std::make_unique<sf::CircleShape>(radius), life_time) {
    GetShape()->setOrigin(radius, radius);
    GetShape()->setPosition(pos);
}

Entity::Type CircleEntity::GetType() { return Entity::Type::Circle; }

std::unique_ptr<b2Shape> CircleEntity::CreateB2Shape() {
    auto b2_shape = std::make_unique<b2CircleShape>();
    dynamic_cast<b2CircleShape *>(b2_shape.get())->m_radius =
        converter::PixelsToMeters<float>(
            dynamic_cast<sf::CircleShape *>(GetShape())->getRadius());
    return b2_shape;
}

}  // namespace foggy
