
#include "GUI/Layout.hpp"

namespace foggy {

Layout::Layout(Widget *parent) : Widget(parent), m_space(5) {}

void Layout::SetSpace(float pixel) {
    if (pixel >= 0) {
        m_space = pixel;
        UpdateShape();
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

void VLayout::Add(Widget *widget) {
    widget->m_parent = this;
    m_widgets.emplace_back(widget);
    UpdateShape();
}

Widget *VLayout::At(uint32_t index) { return m_widgets[index]; }

sf::Vector2f VLayout::GetSize() const {
    float max_x = 0;
    float y = 0;
    for (Widget *widget : m_widgets) {
        sf::Vector2f size = widget->GetSize();
        if (size.x > max_x) {
            max_x = size.x;
        }
        y += m_space + size.y;
    }
    return sf::Vector2f(max_x + m_space * 2, y + m_space);
}

bool VLayout::ProcessEvent(const sf::Event &event,
                           const sf::Vector2f &parent_pos) {
    for (Widget *widget : m_widgets) {
        if (widget->ProcessEvent(event, parent_pos)) return true;
    }
    return false;
}

void VLayout::ProcessEvents(const sf::Vector2f &parent_pos) {
    for (Widget *widget : m_widgets) {
        widget->ProcessEvents(parent_pos);
    }
}

void VLayout::UpdateShape() {
    float max_x = (m_parent ? m_parent->GetSize().x : 0);
    Widget *max_widget =
        *std::max_element(m_widgets.begin(), m_widgets.end(),
                          [](const Widget *lhs, const Widget *rhs) -> bool {
                              return lhs->GetSize().x < rhs->GetSize().x;
                          });
    max_x = std::max(max_x, max_widget->GetSize().x);

    for (Widget *widget : m_widgets) {
        sf::Vector2f size = widget->GetSize();
        float widget_x = size.x;

        if (widget_x > max_x) max_x = widget_x;
    }

    float pos_y = m_space;
    if (m_parent) pos_y = (m_parent->GetSize().y - GetSize().y) / 2.f;

    for (Widget *widget : m_widgets) {
        sf::Vector2f size = widget->GetSize();
        widget->SetPosition((max_x - size.x) / 2.0, pos_y);
        pos_y += size.y + m_space;
    }

    Widget::UpdateShape();
}

void VLayout::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (Widget *widget : m_widgets) {
        widget->draw(target, states);
    }
}

}  // namespace foggy
