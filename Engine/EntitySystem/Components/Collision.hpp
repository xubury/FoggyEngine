#ifndef COLLISION_H
#define COLLISION_H

#include <Box2D/Box2D.h>

#include <SFML/Graphics/Shape.hpp>

#include "EntitySystem/ES.hpp"
#include "util/converter.hpp"

namespace foggy {
namespace component {

struct Collision : es::Component<Collision, es::DefaultEntity> {
   public:
    Collision(es::CollisionSystem *world, b2BodyDef &def, bool debug = true);
    /** Add a fixture to this Collision compoennt. Notice that the fixture's
     * shape is independent to the Transform. So if you want to apply scale to
     * it, you have to scale the shape manually. */
    void AddFixture(const b2FixtureDef &fixture);
    ~Collision();
    b2Body *b2body_ref;
    std::list<std::unique_ptr<sf::Shape>> debug_shape;
    bool debug;
};

}  // namespace component
}  // namespace foggy

#endif /* COLLISION_H */