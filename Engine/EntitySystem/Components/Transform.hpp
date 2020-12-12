#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SFML/Graphics/Transformable.hpp>
#include <iostream>

#include "EntitySystem/ES.hpp"

namespace foggy {
namespace component {

struct Transform : es::Component<Transform, es::DefaultEntity>,
                   sf::Transformable {
   public:
    Transform();
};

}  // namespace component
}  // namespace foggy

#endif /* TRANSFORM_H */
