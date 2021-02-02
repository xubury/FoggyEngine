#include "GUI/Label.hpp"

#include <SFML/Graphics/RenderTarget.hpp>


namespace foggy {
namespace gui {

Label::Label(const std::string &text, const sf::Font &font,
             const sf::Color &color, Widget *parent)
    : Widget(parent) {
    m_text.setFont(font);
    setTextColor(color);
    setText(text);
}

void Label::setText(const std::string &text) {
    m_text.setString(text);
    updateShape();
}

void Label::setCharacterSize(uint32_t size) {
    m_text.setCharacterSize(size);
    updateShape();
}

uint32_t Label::getCharacterSize() const { return m_text.getCharacterSize(); }

void Label::setOrigin(float x, float y) { m_text.setOrigin(x, y); }

sf::Vector2f Label::getSize() const {
    sf::FloatRect rect = m_text.getLocalBounds();
    return sf::Vector2f(rect.width, rect.height);
}

void Label::setTextColor(const sf::Color &color) { m_text.setFillColor(color); }

sf::Color Label::getTextColor() const { return m_text.getFillColor(); }

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.translate(m_pos);
    target.draw(m_text, states);
}

}  // namespace gui
}  // namespace foggy
