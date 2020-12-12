#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <cmath>

#include "util/converter.hpp"
namespace foggy {

/* SFML use Left-handed cooridate es but we use right-handed coordinate
 * es. Also, the camera center is at the center instead of top-left. */
class Camera : public sf::View {
   public:
    friend class World;

   public:
    Camera();
    explicit Camera(const sf::FloatRect &rectangle);
    Camera(const sf::Vector2f &center, const sf::Vector2f &size);

    Camera(const sf::View &view);
    Camera &operator=(const sf::View view);

   private:
    void Update();
};

}  // namespace foggy

#endif /* CAMERA_H */
