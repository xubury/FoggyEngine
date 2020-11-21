#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Entities/EntityManager.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

namespace foggy {
namespace system {
CollisionSystem::CollisionSystem(float x, float y) : b2World(b2Vec2(x, y)) {}

void CollisionSystem::Update(es::EntityManager<es::DefaultEntity> &,
                             const sf::Time &delta_time) {
    Step(delta_time.asSeconds(), 8, 3);
}

void CollisionSystem::AddRigidBody(
    es::EntityManager<es::DefaultEntity> &manager, uint32_t id,
    const sf::Vector2f &pos, b2Shape *shape, b2BodyType type) {
    b2BodyDef body_def;
    body_def.position.Set(converter::PixelsToMeters<float>(pos.x),
                          converter::PixelsToMeters<float>(pos.y));
    body_def.type = type;

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.4;
    fixture_def.restitution = 0.5;
    fixture_def.shape = shape;

    b2Body *res = CreateBody(&body_def);
    res->CreateFixture(&fixture_def);
    manager.GetPtr(id)->Component<component::Collision>()->b2body_ref = res;
}

}  // namespace system
}  // namespace foggy
