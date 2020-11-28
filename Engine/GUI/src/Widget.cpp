#include "GUI/Widget.hpp"

namespace foggy {

Widget::Widget(Widget *parent) : m_parent(parent) {}

void Widget::SetPosition(float x, float y) {
    m_pos.x = x;
    m_pos.y = y;
}

void Widget::SetPosition(const sf::Vector2f &pos) { SetPosition(pos.x, pos.y); }

sf::Vector2f Widget::GetPosition() const { return m_pos; }

bool Widget::ProcessEvent(const sf::Event &, const sf::Vector2f &) {
    return false;
}

void Widget::ProcessEvents(const sf::Vector2f &) {}

void Widget::UpdateShape() {
    if (m_parent != nullptr) {
        m_parent->UpdateShape();
    }
}

}  // namespace foggy
