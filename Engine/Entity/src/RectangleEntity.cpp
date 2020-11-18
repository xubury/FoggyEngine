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

void RectangleEntity::CreateB2Body(b2World &world, b2BodyType type) {
    b2BodyDef body_def;
    sf::Vector2f pos = GetShape()->getPosition();
    body_def.position.Set(converter::PixelsToMeters<float>(pos.x),
                          converter::PixelsToMeters<float>(pos.y));
    body_def.type = type;
    b2PolygonShape b2_shape;
    sf::FloatRect rect =
        dynamic_cast<sf::RectangleShape *>(GetShape())->getLocalBounds();
    b2_shape.SetAsBox(converter::PixelsToMeters(rect.width / 2.0),
                      converter::PixelsToMeters(rect.height / 2.0));

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.4;
    fixture_def.restitution = 0.5;
    fixture_def.shape = &b2_shape;

    b2Body *res = world.CreateBody(&body_def);
    res->CreateFixture(&fixture_def);
    res->SetUserData(this);
    SetB2BodyRef(res);
}

}  // namespace foggy
