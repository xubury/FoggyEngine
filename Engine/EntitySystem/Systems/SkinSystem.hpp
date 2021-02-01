#ifndef SKINSYSTEM_HPP
#define SKINSYSTEM_HPP

#include "EntitySystem/ES.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace es {

class SkinSystem : public es::System<component::Skin, es::DefaultEntity> {
   public:
    SkinSystem() {}
    virtual void update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) override;
};

}  // namespace es
}  // namespace foggy

#endif /* SKINSYSTEM_HPP */
