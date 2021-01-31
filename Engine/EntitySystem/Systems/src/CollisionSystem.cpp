#include "EntitySystem/Systems/CollisionSystem.hpp"

#include <sol/sol.hpp>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Transform.hpp"


namespace foggy {
namespace es {
CollisionSystem::CollisionSystem(float x, float y) : b2World(b2Vec2(x, y)) {}

void CollisionSystem::update(es::EntityManager<es::DefaultEntity> &manager,
                             const sf::Time &delta_time) {
    Step(delta_time.asSeconds(), 8, 3);
    component::Collision::Handle collision;
    auto view = manager.getByComponents(collision);
    auto cur = view.begin();
    auto end = view.end();
    for (; cur != end; ++cur) {
        b2Body *body = collision->b2body_ref;
        b2Vec2 pos(body->GetPosition());
        pos.x = converter::metersToPixels(pos.x);
        pos.y = converter::metersToPixels(pos.y);
        float angle = converter::radToDeg(body->GetAngle());
        cur->component<component::Transform>()->setPosition(pos.x, pos.y);
        cur->component<component::Transform>()->setRotation(angle);
    }
}

}  // namespace es
}  // namespace foggy
