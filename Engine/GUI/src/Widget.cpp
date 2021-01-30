#include "GUI/Widget.hpp"

namespace foggy {
namespace gui {

Widget::Widget(Widget *parent) : m_parent(parent), m_is_visible(true) {}

void Widget::setPosition(float x, float y) {
    m_pos.x = x;
    m_pos.y = y;
}

void Widget::setPosition(const sf::Vector2f &pos) { setPosition(pos.x, pos.y); }

sf::Vector2f Widget::getPosition() const { return m_pos; }

void Widget::hide() {
    if (m_is_visible) {
        m_is_visible = false;
        updateShape();
    }
}

void Widget::show() {
    if (!m_is_visible) {
        m_is_visible = true;
        updateShape();
    }
}

bool Widget::isHidden() const { return !m_is_visible; }

bool Widget::isVisible() const { return m_is_visible; }

void Widget::toggle() {
    m_is_visible = !m_is_visible;
    updateShape();
}

bool Widget::processEvent(const sf::Event &, const sf::Vector2f &) {
    return false;
}

void Widget::processEvents(const sf::Vector2f &) {}

void Widget::updateShape() {
    if (m_parent != nullptr) {
        m_parent->updateShape();
    }
}

}  // namespace gui

}  // namespace foggy
