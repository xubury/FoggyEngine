#include <sol/sol.hpp>

#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Systems/SkinSystem.hpp"

namespace foggy {
namespace es {

void SkinSystem::update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) {
    component::Skin::Handle skin;
    auto view = manager.getByComponents<component::Skin>(skin);
    auto cur = view.begin();
    auto end = view.end();
    for (; cur != end; ++cur) {
        skin->update();
        skin->m_sprite.update(delta_time);
    }
}

}  // namespace es
}  // namespace foggy
