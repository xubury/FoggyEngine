
#include "GUI/Layout.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace foggy {
namespace gui {

Layout::Layout(Widget *parent) : Widget(parent), m_space(5) {
    m_shape.setFillColor(sf::Color(255, 255, 255, 0));
    m_shape.setOutlineColor(sf::Color(0, 0, 255, 255));
    m_shape.setOutlineThickness(1);
}

void Layout::setSpace(float pixel) {
    if (pixel >= 0) {
        m_space = pixel;
        updateShape();
    } else {
        throw std::invalid_argument("pixel value must be >= 0");
    }
}

}  // namespace gui
}  // namespace foggy
