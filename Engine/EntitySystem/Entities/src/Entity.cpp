#include <Box2D/Dynamics/b2Body.h>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Entities/Entity.hpp"

namespace foggy {
namespace es {

ES_INIT_ENTITY(DefaultEntity)

DefaultEntity::DefaultEntity(foggy::es::EntityManager<DefaultEntity> *manager,
                             uint32_t id)
    : Entity<DefaultEntity>(manager, id) {
    m_name = "???";
}

void DefaultEntity::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
    b2Body *body = Component<component::Collision>()->b2body_ref;
    sf::Vector2f position(converter::MetersToPixels(body->GetPosition().x),
                          converter::MetersToPixels(body->GetPosition().y));
    /* Only Y axis is flipped.*/
    position.y = -position.y;
    float rotation = -converter::RadToDeg<float>(body->GetAngle());
    SetPosition(position);
    SetRotation(rotation);
    target.draw(*Component<component::Skin>()->shape, states);
}

void DefaultEntity::SetPosition(const sf::Vector2f &pos) const {
    Component<component::Skin>()->shape->setPosition(pos);
}

void DefaultEntity::SetRotation(float angle) const {
    Component<component::Skin>()->shape->setRotation(angle);
}

}  // namespace es
}  // namespace foggy
