
#include "GUI/Layout.hpp"

namespace foggy {

Layout::Layout(Widget *parent) : Widget(parent), m_space(5) {}

void Layout::setSpace(float pixel) {
    if (pixel >= 0) {
        m_space = pixel;
        updateShape();
    } else {
        throw std::invalid_argument("pixel value must be >= 0");
    }
}

VLayout::VLayout(Widget *parent) : Layout(parent) {}

VLayout::~VLayout() {
    for (Widget *widget : m_widgets) {
        if (widget->m_parent == this) {
            delete widget;
        }
    }
}

void VLayout::add(Widget *widget) {
    widget->m_parent = this;
    m_widgets.emplace_back(widget);
    updateShape();
}

Widget *VLayout::at(uint32_t index) { return m_widgets[index]; }

sf::Vector2f VLayout::getSize() const {
    float max_x = 0;
    float y = 0;
    for (Widget *widget : m_widgets) {
        sf::Vector2f size = widget->getSize();
        if (size.x > max_x) {
            max_x = size.x;
        }
        y += m_space + size.y;
    }
    return sf::Vector2f(max_x + m_space * 2, y + m_space);
}

bool VLayout::processEvent(const sf::Event &event,
                           const sf::Vector2f &parent_pos) {
    for (Widget *widget : m_widgets) {
        if (widget->processEvent(event, parent_pos)) return true;
    }
    return false;
}

void VLayout::processEvents(const sf::Vector2f &parent_pos) {
    for (Widget *widget : m_widgets) {
        widget->processEvents(parent_pos);
    }
}

void VLayout::updateShape() {
    float max_x = (m_parent ? m_parent->getSize().x : 0);
    auto max_widget =
        std::max_element(m_widgets.begin(), m_widgets.end(),
                         [](const Widget *lhs, const Widget *rhs) -> bool {
                             return lhs->getSize().x < rhs->getSize().x;
                         });
    if (max_widget != m_widgets.end())
        max_x = std::max(max_x, (*max_widget)->getSize().x);

    for (Widget *widget : m_widgets) {
        sf::Vector2f size = widget->getSize();
        float widget_x = size.x;

        if (widget_x > max_x) max_x = widget_x;
    }

    float pos_y = m_space;
    if (m_parent) pos_y = (m_parent->getSize().y - getSize().y) / 2.f;

    for (Widget *widget : m_widgets) {
        sf::Vector2f size = widget->getSize();
        widget->setPosition((max_x - size.x) / 2.0, pos_y);
        pos_y += size.y + m_space;
    }

    Widget::updateShape();
}

void VLayout::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (Widget *widget : m_widgets) {
        widget->draw(target, states);
    }
}

}  // namespace foggy
