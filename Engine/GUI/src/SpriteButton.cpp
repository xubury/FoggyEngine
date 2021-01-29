#include "GUI/Sprite.hpp"
#include "GUI/SpriteButton.hpp"

namespace foggy {
namespace gui {

SpriteButton::SpriteButton(const sf::Texture &texture, Widget *parent)
    : Widget(parent), Button(parent), Sprite(texture, parent) {
    m_color = sf::Color::White;
    updateShape();
}

SpriteButton::~SpriteButton() = default;

void SpriteButton::setColor(const sf::Color &color) {
    m_color = color;
    Sprite::setColor(color);
}

void SpriteButton::onMouseEntered() {}

void SpriteButton::onMouseLeft() {}

void SpriteButton::updateShape() { Button::updateShape(); }

void SpriteButton::draw(sf::RenderTarget &target,
                        sf::RenderStates states) const {
    Sprite::draw(target, states);
}

}  // namespace gui

}  // namespace foggy
