#include "GUI/Frame.hpp"

#include "GUI/Configuration.hpp"
#include "GUI/Layout.hpp"

namespace foggy {
namespace gui {

Frame::Frame(sf::RenderWindow &window)
    : Container(nullptr),
      ActionTarget(Configuration::default_gui_inputs),
      m_window(window),
      m_view(m_window.getDefaultView()),
      m_is_dragged(false) {
    ActionTarget::bind(Action(sf::Event::Resized), [this](
                                                       const sf::Event &event) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        this->m_view = sf::View(visibleArea);

        if (Layout *layout = getLayout()) layout->updateShape();
    });
}

void Frame::draw() { m_window.draw(*this); }

void Frame::bind(int key, FuncType &callback) {
    ActionTarget::bind(key, callback);
}

void Frame::unbind(int key) { ActionTarget::unbind(key); }

void Frame::setSize(const sf::Vector2f &size) { m_size = size; }

sf::Vector2f Frame::getSize() const { return m_size; }

bool Frame::processEvent(const sf::Event &event) {
    return processEvent(event, sf::Vector2f(0, 0));
}

void Frame::processEvents() { processEvents(sf::Vector2f(0, 0)); }

bool Frame::processEvent(const sf::Event &event,
                         const sf::Vector2f &parent_pos) {
    bool res = false;
    if (isVisible()) {
        res = ActionTarget::processEvent(event);
        if (!res) {
            res = Container::processEvent(event, parent_pos);
        }
        if (!res) {
            if (event.type == event.MouseButtonPressed && !m_is_dragged) {
                sf::Vector2f mouse_pos(event.mouseButton.x,
                                       event.mouseButton.y);
                sf::Vector2f pos = getPosition() + parent_pos;
                sf::Vector2f size = getSize();
                sf::FloatRect rect(pos.x, pos.y, size.x, 50);
                if (rect.contains(mouse_pos)) {
                    m_is_dragged = true;
                    m_last_mouse_pos = mouse_pos;
                }
            } else if (event.type == event.MouseMoved && m_is_dragged) {
                sf::Vector2f mouse_pos(event.mouseMove.x, event.mouseMove.y);
                sf::Vector2f new_pos =
                    getPosition() + mouse_pos - m_last_mouse_pos;
                m_last_mouse_pos = mouse_pos;
                setPosition(new_pos);
            } else if (event.type == event.MouseButtonReleased) {
                m_is_dragged = false;
            }
        }
    }
    return res;
}

void Frame::processEvents(const sf::Vector2f &parent_pos) {
    if (isVisible()) {
        ActionTarget::processEvents();
        Container::processEvents(parent_pos);
    }
}

void Frame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (isVisible()) {
        sf::View view = target.getView();
        target.setView(m_view);
        Container::draw(target, states);
        target.setView(view);
    }
}

}  // namespace gui
}  // namespace foggy
