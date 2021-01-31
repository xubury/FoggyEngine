#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

#include "GUI/Label.hpp"
#include "GUI/Widget.hpp"

namespace foggy {
namespace gui {

class Button : virtual public Widget {
   public:
    using FuncType = std::function<void(const sf::Event& event, Button& self)>;
    static FuncType defaultFunc;
    Button(Widget* parent = nullptr);
    virtual ~Button() = default;
    FuncType onClick;

   protected:
    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos);

    virtual void onMouseEntered();
    virtual void onMouseLeft();

   private:
    enum Status { None = 0, Hover = 1 };
    Status m_status;
};
}  // namespace gui
}  // namespace foggy

#endif /* BUTTON_H */
