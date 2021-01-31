#include "GUI/HLayout.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace foggy {
namespace gui {

HLayout::HLayout(Widget *parent) : Widget(parent) {}

HLayout::~HLayout() { clear(); }

void HLayout::clear() {
    for (Widget *widget : m_widgets) {
        if (widget->m_parent == this) {
            delete widget;
        }
    }
    m_widgets.clear();
    updateShape();
}

void HLayout::add(Widget *widget) {
    widget->m_parent = this;
    m_widgets.emplace_back(widget);
    updateShape();
}

Widget *HLayout::at(uint32_t index) { return m_widgets[index]; }

sf::Vector2f HLayout::getSize() const {
    float max_y = 0;
    float x = m_space;
    for (Widget *widget : m_widgets) {
        if (widget->isVisible()) {
            sf::Vector2f size = widget->getSize();
            max_y = std::max<float>(size.y, max_y);
            x += m_space + size.x;
        }
    }
    return sf::Vector2f(x, max_y);
}

bool HLayout::processEvent(const sf::Event &event,
                           const sf::Vector2f &parent_pos) {
    sf::Vector2f pos = parent_pos + getPosition();
    for (Widget *widget : m_widgets) {
        if (widget->processEvent(event, pos)) return true;
    }
    return false;
}

void HLayout::processEvents(const sf::Vector2f &parent_pos) {
    sf::Vector2f pos = parent_pos + getPosition();
    for (Widget *widget : m_widgets) {
        widget->processEvents(pos);
    }
}

void HLayout::updateShape() {
    float max_y = 0;
    float pos_x = m_space;
    sf::Vector2f layout_size = getSize();
    if (m_parent) {
        sf::Vector2f parent_size = m_parent->getSize();
        max_y = parent_size.y;
        pos_x = (parent_size.x - layout_size.x) / 2.f;
    }
    for (Widget *widget : m_widgets) {
        if (widget->isVisible()) {
            max_y = std::max<float>(widget->getSize().y, max_y);
        }
    }
    setPosition(pos_x, (max_y - layout_size.y) / 2.f);

    pos_x = m_space;
    for (Widget *widget : m_widgets) {
        if (widget->isVisible()) {
            sf::Vector2f size = widget->getSize();
            widget->setPosition(
                pos_x, (layout_size.y - size.y) / 2.f);  // center alignment
            // layout_size.x - size.x (right alignment)
            // 0 (left alignment)
            pos_x += size.x + m_space;
        }
    }

    m_shape.setSize(getSize());
    Widget::updateShape();
}

void HLayout::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (isVisible()) {
        states.transform.translate(m_pos);
        for (Widget *widget : m_widgets) {
            widget->draw(target, states);
        }
        target.draw(m_shape, states);
    }
}

}  // namespace gui
}  // namespace foggy
