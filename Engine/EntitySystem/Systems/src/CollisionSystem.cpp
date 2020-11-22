#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Entities/EntityManager.hpp"
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
        b2Body *body = cur->Component<component::Collision>()->b2body_ref;
        b2Vec2 pos(body->GetPosition());
        float angle = body->GetAngle();
        pos.y = -pos.y;
        angle = -angle;
        cur->SetPosition(converter::MetersToPixels(pos.x),
                         converter::MetersToPixels(pos.y));
        cur->SetRotation(converter::RadToDeg(angle));
    }
}

}  // namespace es
}  // namespace foggy
