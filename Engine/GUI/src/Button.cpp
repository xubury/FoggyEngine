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
    const sf::Vector2f mouse_pos(event.mouseButton.x, event.mouseButton.y);
    if (event.type == sf::Event::MouseButtonReleased) {
        if (rect.contains(mouse_pos)) {
            OnClick(event, *this);
            res = true;
        }
    } else if (event.type == sf::Event::MouseMoved) {
        Status old_status = m_status;
        m_status = None;
        if (rect.contains(mouse_pos)) {
            m_status = Hover;
        }
        if ((old_status & Hover) && !(m_status & Hover)) {
            OnMouseLeave();
        } else if (!(old_status & Hover) && (m_status & Hover)) {
            OnMouseEnter();
        }
    }
    return res;
}

void Button::OnMouseEnter() {}

void Button::OnMouseLeave() {}

}  // namespace foggy
