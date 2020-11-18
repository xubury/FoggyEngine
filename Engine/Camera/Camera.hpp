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

    sf::Vector2f GetPosition();

    template <typename T>
    sf::Vector2f ViewToWorld(const sf::Vector2<T> &pos);

   private:
};

template <typename T>
sf::Vector2f Camera::ViewToWorld(const sf::Vector2<T> &pos) {
    sf::Vector2f cam_pos = GetPosition();
    sf::Vector2f pos_world;
    pos_world.x = pos.x + cam_pos.x;
    pos_world.y = getSize().y - (pos.y + cam_pos.y);
    return pos_world;
}
}  // namespace foggy

#endif /* CAMERA_H */
