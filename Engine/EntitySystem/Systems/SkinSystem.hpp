#ifndef SKINSYSTEM_H
#define SKINSYSTEM_H

#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace es {

class SkinSystem : public es::System<component::Skin, es::DefaultEntity> {
   public:
    SkinSystem() {}
    virtual void Update(es::EntityManager<es::DefaultEntity> &,
                        const sf::Time &) override {}
};

}  // namespace es
}  // namespace foggy

#endif /* SKINSYSTEM_H */
