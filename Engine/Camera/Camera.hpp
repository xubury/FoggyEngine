#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <cmath>

#include "util/converter.hpp"
namespace foggy {

class Camera : public sf::View {
   public:
    Camera();
    explicit Camera(const sf::FloatRect &rectangle);
    Camera(const sf::Vector2f &center, const sf::Vector2f &size);

    Camera(const sf::View &view);
    Camera &operator=(const sf::View view);

    // Return Camera position in Left Hand Coordinate system
    sf::Vector2f GetPosition() const;

    // Return Camera position in Right Hand(World) Coordinate system
    sf::Vector2f GetWorldPosition() const;

    template <typename T>
    sf::Vector2f ViewToWorld(const sf::RenderTarget &window,
                             const sf::Vector2<T> &pos) const;

    template <typename T>
    void TransformCoordinate(sf::Vector2<T> &pos) const;

    template <typename T>
    void TransformAngle(T &angle) const;

   private:
};

template <typename T>
sf::Vector2f Camera::ViewToWorld(const sf::RenderTarget &window,
                                 const sf::Vector2<T> &pos) const {
    sf::Vector2f normalized;
    sf::FloatRect viewport_normalized = getViewport();
    const sf::Vector2u window_size = window.getSize();
    sf::IntRect viewport(
        static_cast<int>(0.5f + window_size.x * viewport_normalized.left),
        static_cast<int>(0.5f + window_size.y * viewport_normalized.top),
        static_cast<int>(0.5f + window_size.x * viewport_normalized.width),
        static_cast<int>(0.5f + window_size.y * viewport_normalized.height));
    normalized.x = -1.f + 2.f * (pos.x - viewport.left) / viewport.width;
    normalized.y = 1.f - 2.f * (pos.y - viewport.top) / viewport.height;
    normalized = getInverseTransform().transformPoint(normalized);
    // camera to world coordinate
    TransformCoordinate(normalized);
    return normalized;
}

template <typename T>
void Camera::TransformCoordinate(sf::Vector2<T> &pos) const {
    pos.y = getSize().y - pos.y;
}

template <typename T>
void Camera::TransformAngle(T &angle) const {
    angle = -angle;
}

}  // namespace foggy

#endif /* CAMERA_H */
