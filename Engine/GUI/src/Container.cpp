#include <SFML/Graphics/RenderTarget.hpp>

#include "GUI/Container.hpp"
#include "GUI/Layout.hpp"

namespace foggy {
Container::Container(Widget *parent) : Widget(parent), m_layout(nullptr) {}

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

void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (m_layout != nullptr) {
        target.draw(*m_layout, states);
    }
}

bool Container::processEvent(const sf::Event &event,
                             const sf::Vector2f &parent_pos) {
    bool res = false;
    if (m_layout != nullptr) {
        res = m_layout->processEvent(event, parent_pos);
    }
    return res;
}

void Container::processEvents(const sf::Vector2f &parent_pos) {
    if (m_layout != nullptr) {
        m_layout->processEvents(parent_pos);
    }
}

}  // namespace foggy
