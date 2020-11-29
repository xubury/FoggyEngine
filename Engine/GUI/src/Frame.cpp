#include "GUI/Frame.hpp"

namespace foggy {

ActionMap<int> Frame::gui_inputs;

Frame::Frame(sf::RenderWindow &window)
    : Container(nullptr), ActionTarget(gui_inputs), m_window(window) {}

void Frame::Draw() { m_window.draw(*this); }

void Frame::Bind(int key, FuncType &callback) {
    ActionTarget::Bind(key, callback);
}

void Frame::Unbind(int key) { ActionTarget::Unbind(key); }

sf::Vector2f Frame::GetSize() const {
    sf::Vector2u size = m_window.getSize();
    return sf::Vector2f(size.x, size.y);
}

bool Frame::ProcessEvent(const sf::Event &event) {
    sf::Vector2f parent_pos(0, 0);
    return ProcessEvent(event, parent_pos);
}

void Frame::ProcessEvents() {
    sf::Vector2f parent_pos(0, 0);
    ProcessEvents(parent_pos);
}

bool Frame::ProcessEvent(const sf::Event &event,
                         const sf::Vector2f &parent_pos) {
    bool res = ActionTarget::ProcessEvent(event);
    if (!res) {
        res = Container::ProcessEvent(event, parent_pos);
    }
    return res;
}

void Frame::ProcessEvents(const sf::Vector2f &parent_pos) {
    ActionTarget::ProcessEvents();
    Container::ProcessEvents(parent_pos);
    sf::Event event;
    while (m_window.pollEvent(event)) {
        Container::ProcessEvent(event, parent_pos);
    }
}

}  // namespace foggy
