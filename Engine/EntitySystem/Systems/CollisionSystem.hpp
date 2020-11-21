#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace system {

class CollisionSystem
    : public es::System<component::Collision, es::DefaultEntity>,
      public b2World {
   public:
    CollisionSystem(float x, float y);
    virtual void Update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) override;
    void AddRigidBody(es::EntityManager<es::DefaultEntity> &manager,
                      uint32_t id, const sf::Vector2f &pos, b2Shape *shape,
                      b2BodyType type);
};

}  // namespace system
}  // namespace foggy

#endif /* COLLISIONSYSTEM_H */
