#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <Box2D/Box2D.h>

#include "EntitySystem/ES.hpp"
#include "EntitySystem/Entities/Entity.hpp"
#include "Lua/Handler.hpp"

namespace foggy {
namespace es {

class CollisionSystem : public System<component::Collision, es::DefaultEntity>,
                        public b2World {
   public:
    CollisionSystem(float x, float y);
    virtual void Update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) override;
};

class LuaCollision : public LuaHandler<LuaCollision> {
   public:
    void InitComponent(es::EntityManager<es::DefaultEntity> *manager, int id,
                       const std::string &filename) override;

   private:
    friend class foggy::LuaManager;

    LuaCollision(es::SystemManager<es::DefaultEntity> *manager,
                 const std::string &filename);

    void PopulatePolygonFixture(component::Collision *handle);

    void PopulateCircleFixture(component::Collision *handle);

    es::CollisionSystem *m_world;
};

}  // namespace es
}  // namespace foggy

#endif /* COLLISIONSYSTEM_H */
