#include <SFML/Graphics/RenderTarget.hpp>

#include "GUI/Button.hpp"

namespace foggy {

Button::FuncType Button::DefaultFunc = [](const sf::Event &, Button &) {};

Button::Button(Widget *parent)
    : Widget(parent), OnClick(DefaultFunc), m_status(None) {}

bool Button::ProcessEvent(const sf::Event &event,
                          const sf::Vector2f &parent_pos) {
    bool res = false;
    const sf::Vector2f pos = m_pos + parent_pos;
    const sf::Vector2f size = GetSize();
    sf::FloatRect rect;
    rect.left = pos.x;
    rect.top = pos.y;
    rect.width = size.x;
    rect.height = size.y;
    if (event.type == sf::Event::MouseButtonReleased) {
        const sf::Vector2f mouse_pos(event.mouseButton.x, event.mouseButton.y);
        if (rect.contains(mouse_pos)) {
            OnClick(event, *this);
            res = true;
        }
    } else if (event.type == sf::Event::MouseMoved) {
        const sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
        Status old_status = m_status;
        m_status = None;
        if (rect.contains(mouse_pos)) {
            m_status = Hover;
        }
        if ((old_status & Hover) && !(m_status & Hover)) {
            OnMouseLeft();
        } else if (!(old_status & Hover) && (m_status & Hover)) {
            OnMouseEntered();
        }
    }
    return res;
}

void Button::OnMouseEntered() {}

void Button::OnMouseLeft() {}

TextButton::TextButton(const std::string &text, const sf::Color &fill,
                       const sf::Color &outline, float outline_thickness,
                       const sf::Font &font, const sf::Color &color,
                       Widget *parent)
    : Button(parent), m_label(text, font, color, this) {
    SetFillColor(fill);
    SetOutlineColor(outline);
    SetOutlineThickness(outline_thickness);
}

void TextButton::SetText(const std::string &text) { m_label.SetText(text); }

void TextButton::SetCharacterSize(uint32_t size) {
    m_label.SetCharacterSize(size);
}

void TextButton::SetTextColor(const sf::Color &color) {
    m_label.SetTextColor(color);
}

void TextButton::SetFillColor(const sf::Color &color) {
    m_fill_color = color;
    m_shape.setFillColor(color);
}

void TextButton::SetOutlineColor(const sf::Color &color) {
    m_outline_color = color;
    m_shape.setOutlineColor(color);
}

void TextButton::SetOutlineThickness(float thickness) {
    m_shape.setOutlineThickness(thickness);
}

sf::Vector2f TextButton::GetSize() const {
    sf::FloatRect rect = m_shape.getGlobalBounds();
    return sf::Vector2f(rect.width, rect.height);
}

void TextButton::UpdateShape() {
    sf::Vector2f label_size = m_label.GetSize();
    uint32_t char_size = m_label.GetCharacterSize();
    m_shape.setSize(sf::Vector2f(char_size * 2 + label_size.x,
                                 char_size * 2 + label_size.y));
    m_label.SetPosition(char_size, char_size - label_size.y / 2);
    Widget::UpdateShape();
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.translate(m_pos);
    target.draw(m_shape, states);
    target.draw(m_label, states);
}

void TextButton::OnMouseEntered() {
    const float light = 1.4f;
    m_shape.setOutlineColor(sf::Color(m_outline_color.r * light,
                                      m_outline_color.g * light,
                                      m_outline_color.b * light));
    m_shape.setFillColor(sf::Color(m_fill_color.r * light,
                                   m_fill_color.g * light,
                                   m_fill_color.b * light));
}

void TextButton::OnMouseLeft() {
    m_shape.setOutlineColor(m_outline_color);
    m_shape.setFillColor(m_fill_color);
}

}  // namespace foggy
