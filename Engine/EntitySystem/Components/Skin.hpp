#ifndef SKIN_H
#define SKIN_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "EntitySystem/ES.hpp"

namespace foggy {
namespace component {

struct Skin : es::Component<Skin, es::DefaultEntity> {
   public:
    enum Type { Rectangle, Circle };
    Skin(Type type) {
        switch (type) {
            case Rectangle: {
                shape = std::make_unique<sf::RectangleShape>();

                break;
            }
            case Circle: {
                shape = std::make_unique<sf::CircleShape>();
                break;
            }
        }
        shape->setFillColor(sf::Color::Transparent);
        shape->setOutlineColor(sf::Color::Green);
        shape->setOutlineThickness(1.f);
    }
    // TODO: using animation here
    std::unique_ptr<sf::Shape> shape;
};

}  // namespace component
}  // namespace foggy

#endif /* SKIN_H */
