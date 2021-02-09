#include "GUI/Button.hpp"

namespace foggy {
namespace gui {

Button::FuncType Button::defaultFunc = [](const sf::Event &, Button &) {};

Button::Button(Widget *parent)
    : Widget(parent), onClick(defaultFunc), m_status(None) {}

bool Button::processEvent(const sf::Event &event,
                          const sf::Vector2f &parent_pos) {
    bool res = false;
    const sf::Vector2f pos = m_pos + parent_pos;
    const sf::Vector2f size = getSize();
    sf::FloatRect rect;
    rect.left = pos.x;
    rect.top = pos.y;
    rect.width = size.x;
    rect.height = size.y;
    if (event.type == sf::Event::MouseButtonReleased) {
        const sf::Vector2f mouse_pos(event.mouseButton.x, event.mouseButton.y);
        if (rect.contains(mouse_pos)) {
            onClick(event, *this);
            res = true;
        }
    } else if (event.type == sf::Event::MouseMoved) {
        const sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
        Status old_status = m_status;
        m_status = None;
        if (rect.contains(mouse_pos)) {
            m_status = Hover;
            res = true;
        }
        if ((old_status & Hover) && !(m_status & Hover)) {
            onMouseLeft();
        } else if (!(old_status & Hover) && (m_status & Hover)) {
            onMouseEntered();
        }
    }
    return res;
}

void Button::onMouseEntered() {}

void Button::onMouseLeft() {}

}  // namespace gui
}  // namespace foggy
