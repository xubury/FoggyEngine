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

   private:
};

}  // namespace foggy

#endif /* CAMERA_H */
