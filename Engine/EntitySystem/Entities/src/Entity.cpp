#include <Box2D/Dynamics/b2Body.h>

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
    b2Vec2 speed;
    if (Has<component::Collision>()) {
        component::Collision::Handle collision =
            Component<component::Collision>();
        speed = collision->b2body_ref->GetLinearVelocity();
        if (collision->debug) {
            for (const auto &shape : collision->debug_shape)
                target.draw(*shape, states);
        }
    }
    if (Has<component::Skin>()) {
        component::Skin::Handle skin = Component<component::Skin>();
        if (speed.x > converter::PixelsToMeters(100.0f)) {
            skin->m_sprite.SetAnimation(skin->m_animations.at(1));
        } else {
            skin->m_sprite.SetAnimation(skin->m_animations.at(0));
        }
        target.draw(skin->m_sprite, states);
    }
}

void DefaultEntity::SetPosition(float x, float y) {
    Component<component::Transform>()->SetPosition(x, y);
}

void DefaultEntity::SetPosition(const sf::Vector2f &pos) {
    SetPosition(pos.x, pos.y);
}

sf::Vector2f DefaultEntity::GetPosition() const {
    return Component<component::Transform>()->GetPosition();
}

void DefaultEntity::SetRotation(float angle) {
    Component<component::Transform>()->SetRotation(angle);
}

float DefaultEntity::GetRotation() const {
    return Component<component::Transform>()->GetRotation();
}

}  // namespace es
}  // namespace foggy
