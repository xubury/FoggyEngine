#include <box2d/b2_body.h>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace es {

ES_INIT_ENTITY(DefaultEntity)

DefaultEntity::DefaultEntity(foggy::es::EntityManager<DefaultEntity> *manager,
                             uint32_t id)
    : Entity<DefaultEntity>(manager, id) {
    manager->AddComponent<component::Transform>(id);
    m_name = "???";
}

void DefaultEntity::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
    const sf::Transform &trans =
        Component<component::Transform>()->getTransform();
    states.transform = trans;
    if (Has<component::Collision>()) {
        component::Collision::Handle collision =
            Component<component::Collision>();
        if (collision->debug) {
            for (const auto &shape : collision->debug_shape)
                target.draw(*shape, states);
        }
    }
}

}  // namespace es
}  // namespace foggy
