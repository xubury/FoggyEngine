#ifndef SKINSYSTEM_H
#define SKINSYSTEM_H

#include "EntitySystem/ES.hpp"
#include "EntitySystem/Entities/Entity.hpp"
#include "Lua/Handler.hpp"

namespace foggy {
namespace es {

class SkinSystem : public es::System<component::Skin, es::DefaultEntity> {
   public:
    SkinSystem() {}
    virtual void Update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) override;
};

class LuaAnimation : public LuaHandler<LuaAnimation> {
   public:
    LuaAnimation(es::SystemManager<es::DefaultEntity> *manager,
                 const std::string &filename);
    void InitComponent(es::EntityManager<es::DefaultEntity> *manager, int id,
                       const std::string &filename) override;
};

}  // namespace es
}  // namespace foggy

#endif /* SKINSYSTEM_H */
