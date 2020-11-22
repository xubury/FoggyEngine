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
    target.draw(*Component<component::Skin>()->shape, states);
}

void DefaultEntity::SetPosition(float x, float y) {
    Component<component::Skin>()->shape->setPosition(x, -y);
}

void DefaultEntity::SetPosition(const sf::Vector2f &pos) {
    SetPosition(pos.x, pos.y);
}

sf::Vector2f DefaultEntity::GetPosition() const {
    sf::Vector2f pos(Component<component::Skin>()->shape->getPosition());
    pos.y = -pos.y;
    return pos;
}

void DefaultEntity::SetRotation(float angle) {
    Component<component::Skin>()->shape->setRotation(-angle);
}

float DefaultEntity::GetRotation() const {
    return -Component<component::Skin>()->shape->getRotation();
}

}  // namespace es
}  // namespace foggy
