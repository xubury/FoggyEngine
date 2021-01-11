#include <box2d/box2d.h>

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
    manager->addComponent<component::Transform>(id);
    m_name = "???";
}

void DefaultEntity::setPosition(const sf::Vector2f &pos) {
    component<component::Transform>()->setPosition(pos);
}

sf::Vector2f DefaultEntity::getPosition() const {
    return component<component::Transform>()->getPosition();
}

void DefaultEntity::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
    const sf::Transform &trans =
        component<component::Transform>()->getTransform();
    states.transform = trans;
    if (has<component::Collision>()) {
        component::Collision::Handle collision =
            component<component::Collision>();
        if (collision->debug) {
            for (const auto &shape : collision->debug_shape)
                target.draw(*shape, states);
        }
    }
}

}  // namespace es
}  // namespace foggy
