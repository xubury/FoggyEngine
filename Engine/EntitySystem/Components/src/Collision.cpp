#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

namespace foggy {
namespace component {

Collision::Collision(es::CollisionSystem *world, b2BodyDef &def) {
    b2body_ref = world->CreateBody(&def);
}

void Collision::AddFixture(const b2FixtureDef &fixture) {
    b2body_ref->CreateFixture(&fixture);
}

Collision::~Collision() { b2body_ref->GetWorld()->DestroyBody(b2body_ref); }
}  // namespace component
}  // namespace foggy
