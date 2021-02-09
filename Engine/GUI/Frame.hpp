#ifndef FRAME_HPP
#define FRAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "ActionSystem/ActionTarget.hpp"
#include "GUI/Container.hpp"

namespace foggy {
namespace gui {

class Frame : public Container, protected ActionTarget<int> {
   public:
    using ActionTarget<int>::FuncType;
    Frame(sf::RenderWindow& window);
    virtual ~Frame() = default;

    bool processEvent(const sf::Event& event);
    void processEvents();

    void bind(int key, FuncType& callback);
    void unbind(int key);
    void draw();

    void setSize(const sf::Vector2f& size);
    virtual sf::Vector2f getSize() const override;

   private:
    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos) override;
    virtual void processEvents(const sf::Vector2f& parent_pos) override;

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;

   private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_size;
    sf::View m_view;
    sf::Vector2f m_last_mouse_pos;
    bool m_is_dragged;
};

}  // namespace gui
}  // namespace foggy

#endif /* FRAME_HPP */
