#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

namespace foggy {
namespace es {
CollisionSystem::CollisionSystem(float x, float y) : b2World(b2Vec2(x, y)) {}

void CollisionSystem::Update(es::EntityManager<es::DefaultEntity> &manager,
                             const sf::Time &delta_time) {
    Step(delta_time.asSeconds(), 8, 3);
    component::Collision::Handle handle;
    auto view = manager.GetByComponents(handle);
    auto cur = view.Begin();
    auto end = view.End();
    for (; cur != end; ++cur) {
        component::Collision::Handle collision =
            cur->Component<component::Collision>();
        b2Body *body = collision->b2body_ref;
        b2Vec2 pos(body->GetPosition());
        pos.x = converter::MetersToPixels(pos.x);
        pos.y = -converter::MetersToPixels(pos.y);
        float angle = -converter::DegToRad(body->GetAngle());
        for (const auto &shape : collision->debug_shape) {
            shape->setPosition(pos.x, pos.y);
            shape->setRotation(angle);
        }
    }
}

}  // namespace es
}  // namespace foggy
