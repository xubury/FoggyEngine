#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <Box2D/Box2D.h>

#include "EntitySystem/Components/Collision.hpp"
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
    void InitSystem(es::SystemManager<es::DefaultEntity> *manager);

    void InitComponent(es::EntityManager<es::DefaultEntity> *manager, int id,
                       const std::string &filename);

   private:
    friend class foggy::LuaManager;

    LuaCollision() : m_world(nullptr){};

    void PopulatePolygonFixture(component::Collision::Handle &handle);

    es::CollisionSystem *m_world;
};

}  // namespace es
}  // namespace foggy

#endif /* COLLISIONSYSTEM_H */
