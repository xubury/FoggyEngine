#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

namespace foggy {
namespace es {
CollisionSystem::CollisionSystem(float x, float y) : b2World(b2Vec2(x, y)) {}

void CollisionSystem::Update(es::EntityManager<es::DefaultEntity> &manager,
                             const sf::Time &delta_time) {
    Step(delta_time.asSeconds(), 8, 3);
    component::Collision::Handle collision;
    auto view = manager.GetByComponents(collision);
    auto cur = view.Begin();
    auto end = view.End();
    for (; cur != end; ++cur) {
        b2Body *body = collision->b2body_ref;
        b2Vec2 pos(body->GetPosition());
        pos.x = converter::MetersToPixels(pos.x);
        pos.y = converter::MetersToPixels(pos.y);
        float angle = converter::DegToRad(body->GetAngle());
        cur->Component<component::Transform>()->SetPosition(pos.x, pos.y);
        cur->Component<component::Transform>()->SetRotation(angle);
        if (collision->debug) {
            for (const auto &shape : collision->debug_shape) {
                shape->setPosition(pos.x, -pos.y);
                shape->setRotation(-angle);
            }
        }
    }
}

}  // namespace es
}  // namespace foggy
