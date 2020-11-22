#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/Graphics/Transformable.hpp>

#include "EntitySystem/ES.hpp"

namespace foggy {
namespace component {

struct Transform : es::Component<Transform, es::DefaultEntity>,
                   private sf::Transformable {
   public:
    Transform();
    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f &pos);
    sf::Vector2f GetPosition() const;

    void SetRotation(float angle);
    float GetRotation() const;
};

}  // namespace component
}  // namespace foggy

#endif /* TRANSFORM_H */
