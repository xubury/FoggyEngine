#include <sol/sol.hpp>

#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Systems/SkinSystem.hpp"

namespace foggy {
namespace es {

void SkinSystem::Update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) {
    component::Skin::Handle skin;
    auto view = manager.GetByComponents<component::Skin>(skin);
    auto cur = view.Begin();
    auto end = view.End();
    for (; cur != end; ++cur) {
        skin->m_sprite.Update(delta_time);
    }
}

}  // namespace es
}  // namespace foggy
