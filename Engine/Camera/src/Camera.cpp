#include "Camera/Camera.hpp"

namespace foggy {

Camera::Camera() {}

Camera::Camera(const sf::FloatRect &rectangle) : sf::View(rectangle) {}

Camera::Camera(const sf::Vector2f &center, const sf::Vector2f &size)
    : sf::View(center, size) {}

Camera::Camera(const sf::View &view) : sf::View(view) {}

Camera &Camera::operator=(sf::View view) {
    std::swap(*dynamic_cast<sf::View *>(this), view);
    return *this;
}

void Camera::Move(const int x, const int y) { move(x, -y); }

void Camera::Resize(const int width, const int height) {
    sf::Vector2f pos = GetPosition();
    setCenter(pos.x + width / 2.f, -pos.y + height / 2.f);
    setSize(width, height);
}

sf::Vector2f Camera::GetPosition() const {
    sf::Vector2f pos(getCenter().x - getSize().x / 2,
                     -getCenter().y + getSize().y / 2);
    return pos;
}

sf::Vector2f Camera::GetCenter() const {
    sf::Vector2f center(getCenter());
    center.y = -center.y;
    return center;
}

void Camera::Update() {
    if (m_track_entity != nullptr) {
        // TODO: Not to track it if no one else owns it?
        // if (m_track_entity.use_count() == 1) {
        // m_track_entity.reset();
        // }
        sf::Vector2f target = m_track_entity->GetPosition();
        sf::Vector2f dir = target - GetCenter();
        Move(dir.x, dir.y);
    }
}

void Camera::TrackEntity(const Entity::Ptr &entity) { m_track_entity = entity; }

}  // namespace foggy
