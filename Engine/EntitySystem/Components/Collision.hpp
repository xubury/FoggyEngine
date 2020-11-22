#ifndef COLLISION_H
#define COLLISION_H

#include <Box2D/Box2D.h>

#include "EntitySystem/ES.hpp"
#include "util/converter.hpp"

namespace foggy {
namespace component {

struct Collision : es::Component<Collision, es::DefaultEntity> {
   public:
    Collision(es::CollisionSystem *world, b2BodyDef &def);
    void AddFixture(const b2FixtureDef &fixture);
    ~Collision();
    b2Body *b2body_ref;
};

}  // namespace component
}  // namespace foggy

#endif /* COLLISION_H */
