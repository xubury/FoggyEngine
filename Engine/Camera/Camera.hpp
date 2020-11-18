#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
namespace foggy {

class Camera : public sf::View {
   public:
    Camera();
    explicit Camera(const sf::FloatRect &rectangle);
    Camera(const sf::Vector2f &center, const sf::Vector2f &size);

    Camera(const sf::View &view);
    Camera &operator=(const sf::View view);

    sf::Vector2f GetPosition() const;

    template <typename T>
    sf::Vector2f ViewToWorld(const sf::RenderWindow &window,
                             const sf::Vector2<T> &pos) const;

    template <typename T>
    void TransformCoordinate(sf::Vector2<T> &pos) const;

    template <typename T>
    void TransformAngle(T &angle) const;

   private:
};

template <typename T>
sf::Vector2f Camera::ViewToWorld(const sf::RenderWindow &window,
                                 const sf::Vector2<T> &pos) const {
    sf::Vector2f pos_world(pos);
    const sf::FloatRect &viewport = getViewport();
    const sf::Vector2u window_size = window.getSize();
    pos_world.x =
        (pos_world.x - viewport.left * window_size.x) / viewport.width;
    pos_world.y =
        (pos_world.y - viewport.top * window_size.y) / viewport.height;
    pos_world += GetPosition();
    TransformCoordinate(pos_world);
    return pos_world;
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
