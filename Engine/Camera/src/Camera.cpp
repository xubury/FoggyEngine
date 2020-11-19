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
    sf::FloatRect visibleArea(pos.x, pos.y, width, height);
    reset(visibleArea);
}

sf::Vector2f Camera::GetPosition() const {
    sf::Vector2f pos(getCenter().x - getSize().x / 2,
                     -getCenter().y + getSize().y / 2);
    return pos;
}

}  // namespace foggy
