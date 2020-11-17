#include <SFML/Graphics/RectangleShape.hpp>

#include "Entity/RectangleEntity.hpp"

namespace foggy {

RectangleEntity::RectangleEntity(const sf::Vector2f &pos,
                                 const sf::Vector2f &size,
                                 const sf::Time &life_time)
    : Entity(std::make_unique<sf::RectangleShape>(size), life_time) {
    GetShape()->setOrigin(size.x / 2, size.y / 2);
    GetShape()->setPosition(pos);
}

Entity::Type RectangleEntity::GetType() { return Type::Rectangle; }

std::unique_ptr<b2Shape> RectangleEntity::CreateB2Shape() {
    std::unique_ptr<b2Shape> b2_shape = std::make_unique<b2PolygonShape>();
    sf::FloatRect rect = GetShape()->getLocalBounds();
    dynamic_cast<b2PolygonShape *>(b2_shape.get())
        ->SetAsBox(converter::PixelsToMeters<float>(rect.width / 2.0),
                   converter::PixelsToMeters<float>(rect.height / 2.0));
    return b2_shape;
}

}  // namespace foggy
