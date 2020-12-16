#include <SFML/Graphics/RenderTarget.hpp>

#include "GUI/Label.hpp"

namespace foggy {

Label::Label(const std::string &text, const sf::Font &font,
             const sf::Color &color, Widget *parent)
    : Widget(parent) {
    m_text.setFont(font);
    SetTextColor(color);
    SetText(text);
}

void Label::SetText(const std::string &text) {
    m_text.setString(text);
    UpdateShape();
}

void Label::SetCharacterSize(uint32_t size) {
    m_text.setCharacterSize(size);
    UpdateShape();
}

uint32_t Label::GetCharacterSize() const { return m_text.getCharacterSize(); }

void Label::SetOrigin(float x, float y) {
    m_text.setOrigin(x, y);
}

sf::Vector2f Label::GetSize() const {
    sf::FloatRect rect = m_text.getGlobalBounds();
    return sf::Vector2f(rect.width, rect.height);
}

void Label::SetTextColor(const sf::Color &color) { m_text.setFillColor(color); }

sf::Color Label::GetTextColor() const {
    return m_text.getFillColor();
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.translate(m_pos);
    target.draw(m_text, states);
}

}  // namespace foggy
