#ifndef SKINSYSTEM_H
#define SKINSYSTEM_H

#include <EntitySystem/Components/Skin.hpp>

#include "EntitySystem/ES.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace es {

class SkinSystem : public es::System<component::Skin, es::DefaultEntity> {
   public:
    SkinSystem() {}
    virtual void Update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) override {
        component::Skin::Handle skin;
        auto view = manager.GetByComponents<component::Skin>(skin);
        auto cur = view.Begin();
        auto end = view.End();
        for (; cur != end; ++cur) {
            skin->m_sprite.Update(delta_time);
        }
    }
};

}  // namespace es
}  // namespace foggy

#endif /* SKINSYSTEM_H */
