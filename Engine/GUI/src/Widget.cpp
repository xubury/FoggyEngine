#include "GUI/Widget.hpp"

namespace foggy {

Widget::Widget(Widget *parent) : m_parent(parent) {}

void Widget::setPosition(float x, float y) {
    m_pos.x = x;
    m_pos.y = y;
}

void Widget::setPosition(const sf::Vector2f &pos) { setPosition(pos.x, pos.y); }

sf::Vector2f Widget::getPosition() const { return m_pos; }

bool Widget::processEvent(const sf::Event &, const sf::Vector2f &) {
    return false;
}

void Widget::processEvents(const sf::Vector2f &) {}

void Widget::updateShape() {
    if (m_parent != nullptr) {
        m_parent->updateShape();
    }
}

}  // namespace foggy
