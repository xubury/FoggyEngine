#ifndef CAMERA_H
#define CAMERA_H

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
    sf::Vector2f ViewToWorld(const sf::Vector2<T> &pos) const;
    template <typename T>
    sf::Vector2f WorldToView(const sf::Vector2<T> &pos) const;

   private:
};

template <typename T>
sf::Vector2f Camera::ViewToWorld(const sf::Vector2<T> &pos) const {
    sf::Vector2f pos_world;
    pos_world.x = pos.x;
    pos_world.y = getSize().y - pos.y;
    return pos_world;
}

template <typename T>
sf::Vector2f Camera::WorldToView(const sf::Vector2<T> &pos) const {
    sf::Vector2f pos_view;
    pos_view.x = pos.x;
    pos_view.y = getSize().y - pos.y;
    return pos_view;
}

}  // namespace foggy

#endif /* CAMERA_H */
