#ifndef COLLISION_H
#define COLLISION_H

#include <box2d/box2d.h>

#include <SFML/Graphics/Shape.hpp>

#include "EntitySystem/ES.hpp"
#include "util/converter.hpp"

namespace foggy {
namespace component {

struct Collision : es::Component<Collision, es::DefaultEntity> {
   public:
    Collision(b2BodyDef &def, bool debug = true);
    ~Collision();
    /** add a fixture to this Collision component. Notice that the fixture's
     * shape is independent to the Transform. So if you want to apply scale to
     * it, you have to scale the shape manually. */
    void addFixture(const b2FixtureDef &fixture);

    b2Body *b2body_ref;
    b2BodyDef b2body_def;
    std::list<std::unique_ptr<sf::Shape>> debug_shape;
    bool debug;
};

}  // namespace component
}  // namespace foggy

#endif /* COLLISION_H */
