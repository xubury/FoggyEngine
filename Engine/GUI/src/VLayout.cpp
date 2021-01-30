
#include "GUI/VLayout.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace foggy {
namespace gui {

VLayout::VLayout(Widget *parent) : Layout(parent) {}

VLayout::~VLayout() { clear(); }

void VLayout::clear() {
    for (Widget *widget : m_widgets) {
        if (widget->m_parent == this) {
            delete widget;
        }
    }
    m_widgets.clear();
    updateShape();
}

void VLayout::add(Widget *widget) {
    widget->m_parent = this;
    m_widgets.emplace_back(widget);
    updateShape();
}

Widget *VLayout::at(uint32_t index) { return m_widgets[index]; }

sf::Vector2f VLayout::getSize() const {
    float max_x = 0;
    float y = m_space;
    for (Widget *widget : m_widgets) {
        sf::Vector2f size = widget->getSize();
        if (size.x > max_x) {
            max_x = size.x;
        }
        y += m_space + size.y;
    }
    return sf::Vector2f(max_x, y);
}

bool VLayout::processEvent(const sf::Event &event,
                           const sf::Vector2f &parent_pos) {
    sf::Vector2f pos = parent_pos + getPosition();
    for (Widget *widget : m_widgets) {
        if (widget->processEvent(event, pos)) return true;
    }
    return false;
}

void VLayout::processEvents(const sf::Vector2f &parent_pos) {
    sf::Vector2f pos = parent_pos + getPosition();
    for (Widget *widget : m_widgets) {
        widget->processEvents(pos);
    }
}

void VLayout::updateShape() {
    float max_x = 0;
    float pos_y = m_space;
    sf::Vector2f layout_size = getSize();
    if (m_parent) {
        sf::Vector2f parent_size = m_parent->getSize();
        max_x = parent_size.x;
        pos_y = (parent_size.y - layout_size.y) / 2.f;
    }
    for (Widget *widget : m_widgets) {
        if (widget->isVisible()) {
            sf::Vector2f size = widget->getSize();
            float widget_x = size.x;

            if (widget_x > max_x) max_x = widget_x;
        }
    }
    setPosition((max_x - layout_size.x) / 2.f, pos_y);

    pos_y = m_space;
    for (Widget *widget : m_widgets) {
        if (widget->isVisible()) {
            sf::Vector2f size = widget->getSize();
            widget->setPosition((layout_size.x - size.x) / 2.f, pos_y);
            pos_y += size.y + m_space;
        }
    }

    m_shape.setSize(getSize());
    Widget::updateShape();
}

void VLayout::draw(sf::RenderTarget &target, sf::RenderStates states) const {
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