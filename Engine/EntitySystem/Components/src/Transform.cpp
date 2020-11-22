#include "EntitySystem/Components/Transform.hpp"
namespace foggy {
namespace component {

Transform::Transform() {}

void Transform::SetPosition(float x, float y) { setPosition(x, -y); }

void Transform::SetPosition(const sf::Vector2f &pos) {
    SetPosition(pos.x, pos.y);
}

sf::Vector2f Transform::GetPosition() const {
    sf::Vector2f pos(getPosition());
    pos.y = -pos.y;
    return pos;
}

void Transform::SetRotation(float angle) { setRotation(-angle); }
float Transform::GetRotation() const { return -getRotation(); }

}  // namespace component
}  // namespace foggy
