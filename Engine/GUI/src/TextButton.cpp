#include "GUI/TextButton.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "GUI/Configuration.hpp"

namespace foggy {
namespace gui {

TextButton::TextButton(const std::string &text, const sf::Color &fill,
                       const sf::Color &outline, float outline_thickness,
                       const sf::Font &font, const sf::Color &color,
                       Widget *parent)
    : Button(parent), m_label(text, font, color, this) {
    setFillColor(fill);
    setOutlineColor(outline);
    setOutlineThickness(outline_thickness);
}

void TextButton::setText(const std::string &text) { m_label.setText(text); }

void TextButton::setCharacterSize(uint32_t size) {
    m_label.setCharacterSize(size);
}

void TextButton::setTextColor(const sf::Color &color) {
    m_label.setTextColor(color);
}

void TextButton::setFillColor(const sf::Color &color) {
    m_fill_color = color;
    m_shape.setFillColor(color);
}

void TextButton::setOutlineColor(const sf::Color &color) {
    m_outline_color = color;
    m_shape.setOutlineColor(color);
}

void TextButton::setOutlineThickness(float thickness) {
    m_outline_thickness = thickness;
    m_shape.setOutlineThickness(thickness);
}

sf::Vector2f TextButton::getSize() const {
    sf::FloatRect rect = m_shape.getGlobalBounds();
    return sf::Vector2f(rect.width, rect.height);
}

void TextButton::updateShape() {
    sf::Vector2f label_size = m_label.getSize();
    uint32_t char_size = m_label.getCharacterSize();
    m_shape.setSize(sf::Vector2f(char_size * 2 + label_size.x,
                                 char_size * 2 + label_size.y));
    m_label.setPosition(char_size, char_size - label_size.y / 2);
    Widget::updateShape();
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Vector2f outline(m_outline_thickness, m_outline_thickness);
    states.transform.translate(m_pos + outline);
    target.draw(m_shape, states);
    target.draw(m_label, states);
}

void TextButton::onMouseEntered() {
    m_shape.setOutlineColor(
        sf::Color(m_outline_color.r * Configuration::Colors::lighting,
                  m_outline_color.g * Configuration::Colors::lighting,
                  m_outline_color.b * Configuration::Colors::lighting));
    m_shape.setFillColor(
        sf::Color(m_fill_color.r * Configuration::Colors::lighting,
                  m_fill_color.g * Configuration::Colors::lighting,
                  m_fill_color.b * Configuration::Colors::lighting));
}

void TextButton::onMouseLeft() {
    m_shape.setOutlineColor(m_outline_color);
    m_shape.setFillColor(m_fill_color);
}

}  // namespace gui
}  // namespace foggy