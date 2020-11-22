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
    Skin() {}
    // TODO: using animation here
};

}  // namespace component
}  // namespace foggy

#endif /* SKIN_H */
