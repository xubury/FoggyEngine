#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <Box2D/Box2D.h>

#include "EntitySystem/ES.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace es {

class CollisionSystem : public System<component::Collision, es::DefaultEntity>,
                        public b2World {
   public:
    CollisionSystem(float x, float y);
    virtual void Update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) override;
};

}  // namespace es
}  // namespace foggy

#endif /* COLLISIONSYSTEM_H */
