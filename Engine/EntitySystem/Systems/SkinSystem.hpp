#ifndef SKINSYSTEM_H
#define SKINSYSTEM_H

#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace system {

class SkinSystem : public es::System<component::Skin, es::DefaultEntity> {
   public:
    SkinSystem() {}
    virtual void Update(es::EntityManager<es::DefaultEntity> &,
                        const sf::Time &) override {}
};

}  // namespace system
}  // namespace foggy

#endif /* SKINSYSTEM_H */
