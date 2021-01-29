#include <SFML/Graphics/RenderTarget.hpp>

#include "GUI/Sprite.hpp"

namespace foggy {
namespace gui {

Sprite::Sprite(const sf::Texture &texture, Widget *parent)
    : Widget(parent), m_sprite(texture) {
    m_color = m_sprite.getColor();
    updateShape();
}

Sprite::~Sprite() = default;

void Sprite::setTexture(const sf::Texture &texture, bool reset_rect) {
    m_sprite.setTexture(texture, reset_rect);
    updateShape();
}

void Sprite::SetTextureRect(const sf::IntRect &rect) {
    m_sprite.setTextureRect(rect);
}

void Sprite::setColor(const sf::Color &color) {
    m_color = color;
    m_sprite.setColor(color);
}

sf::Vector2f Sprite::getSize() const {
    sf::FloatRect rect = m_sprite.getGlobalBounds();
    return sf::Vector2f(rect.width, rect.height);
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.translate(m_pos);
    target.draw(m_sprite, states);
}

}  // namespace gui

}  // namespace foggy
