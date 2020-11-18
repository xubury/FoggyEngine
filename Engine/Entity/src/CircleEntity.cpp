
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

void CircleEntity::CreateB2Body(b2World &world, b2BodyType type) {
    b2BodyDef body_def;
    sf::Vector2f pos = GetShape()->getPosition();
    body_def.position.Set(converter::PixelsToMeters<float>(pos.x),
                          converter::PixelsToMeters<float>(pos.y));
    body_def.type = type;
    b2CircleShape b2_shape;
    b2_shape.m_radius = converter::PixelsToMeters(
        dynamic_cast<sf::CircleShape *>(GetShape())->getRadius());

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0 / (b2_shape.m_radius * b2_shape.m_radius);
    fixture_def.friction = 0.4;
    fixture_def.restitution = 0.5;
    fixture_def.shape = &b2_shape;

    b2Body *res = world.CreateBody(&body_def);
    res->CreateFixture(&fixture_def);
    res->SetUserData(this);
    SetB2BodyRef(res);
}

}  // namespace foggy
