#ifndef FRAME_H
#define FRAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "ActionSystem/ActionTarget.hpp"
#include "GUI/Container.hpp"

namespace foggy {

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

    virtual sf::Vector2f getSize() const override;

   private:
    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos) override;
    virtual void processEvents(const sf::Vector2f& parent_pos) override;

   private:
    static ActionMap<int> gui_inputs;

    sf::RenderWindow& m_window;
};

}  // namespace foggy

#endif /* FRAME_H */
