#include "GUI/Container.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "GUI/Layout.hpp"

namespace foggy {
namespace gui {

Container::Container(Widget *parent) : Widget(parent), m_layout(nullptr) {
    setFillColor(sf::Color(255, 255, 255, 0));
    setOutlineColor(sf::Color(255, 0, 0, 255));
    setOutlineThickness(1);
}

Container::~Container() {
    if (m_layout != nullptr && m_layout->m_parent == this) {
        m_layout->m_parent = nullptr;
        delete m_layout;
    }
}

void Container::setLayout(Layout *layout) {
    if (m_layout != nullptr && m_layout->m_parent == this) {
        m_layout->m_parent = nullptr;
        delete m_layout;
    }
    if ((m_layout = layout) != nullptr) {
        m_layout->m_parent = this;
        m_layout->updateShape();
    }
}

Layout *Container::getLayout() const { return m_layout; }

sf::Vector2f Container::getSize() const {
    sf::Vector2f res(0, 0);
    if (m_layout != nullptr) {
        res = m_layout->getSize();
    }
    return res;
}

void Container::clear() {
    if (m_layout != nullptr) {
        m_layout->clear();
        updateShape();
    }
}

void Container::setFillColor(const sf::Color &color) {
    m_shape.setFillColor(color);
}

void Container::setOutlineColor(const sf::Color &color) {
    m_shape.setOutlineColor(color);
}

void Container::setOutlineThickness(float thickness) {
    m_shape.setOutlineThickness(thickness);
}

void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (isVisible() && m_layout != nullptr) {
        states.transform.translate(m_pos);
        target.draw(m_shape, states);
        target.draw(*m_layout, states);
    }
}

bool Container::processEvent(const sf::Event &event,
                             const sf::Vector2f &parent_pos) {
    bool res = false;
    if (isVisible() && m_layout != nullptr) {
        res = m_layout->processEvent(event, parent_pos);
    }
    return res;
}

void Container::processEvents(const sf::Vector2f &parent_pos) {
    if (isVisible() && m_layout != nullptr) {
        m_layout->processEvents(parent_pos);
    }
}

void Container::updateShape() {
    sf::Vector2f size = getSize();
    m_shape.setSize(size);
    Widget::updateShape();
}

}  // namespace gui
}  // namespace foggy
