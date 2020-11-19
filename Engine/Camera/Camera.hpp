#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <cmath>

#include "util/converter.hpp"
namespace foggy {

/* SFML use Left-handed cooridate system but we use right-handed coordinate
 * system. Also, the camera center is at the center instead of top-left. */
class Camera : sf::View {
   public:
    Camera();
    explicit Camera(const sf::FloatRect &rectangle);
    Camera(const sf::Vector2f &center, const sf::Vector2f &size);

    Camera(const sf::View &view);
    Camera &operator=(const sf::View view);

    void Resize(const int width, const int height);

    void Move(const int x, const int y);

    // Return Camera position in Right Hand Coordinate system
    sf::Vector2f GetPosition() const;

    template <typename T>
    sf::Vector2f ViewToWorld(const sf::RenderTarget &window,
                             const sf::Vector2<T> &pos) const;

    friend class World;

   private:
    template <typename T>
    void CenterToTopLeft(sf::Vector2<T> &pos) const;

    template <typename T>
    void TopLeftToCenter(sf::Vector2<T> &pos) const;
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
    /* Convert camera(normalized) to world coordinate, transformPoint accept
     * right hand coordinate. But it return a left hand coordinate(SFML
     * coordinate) */
    normalized = getInverseTransform().transformPoint(normalized);
    TopLeftToCenter(normalized);
    return normalized;
}

template <typename T>
void Camera::CenterToTopLeft(sf::Vector2<T> &pos) const {
    pos.x = pos.x + getSize().x / 2;
    pos.y = getSize().y / 2 - pos.y;
}

template <typename T>
void Camera::TopLeftToCenter(sf::Vector2<T> &pos) const {
    pos.x = pos.x - getSize().x / 2;
    pos.y = getSize().y / 2 - pos.y;
}

}  // namespace foggy

#endif /* CAMERA_H */
