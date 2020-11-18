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

sf::Vector2f Camera::GetPosition() {
    return getCenter() - sf::Vector2f(getSize().x / 2, getSize().y / 2);
}

}  // namespace foggy
