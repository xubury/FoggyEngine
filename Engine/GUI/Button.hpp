#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include "GUI/Widget.hpp"

namespace foggy {

class Button : public Widget {
   public:
    using FuncType = std::function<void(const sf::Event &event, Button &self)>;
    static FuncType DefaultFunc;
    Button(Widget *parent = nullptr);
    virtual ~Button() = default;
    FuncType OnClick;

   protected:
    virtual bool ProcessEvent(const sf::Event &event,
                              const sf::Vector2f &parent_pos);

    virtual void OnMouseEnter();
    virtual void OnMouseLeave();

   private:
    enum Status { None = 0, Hover = 1 };
    Status m_status;
};

}  // namespace foggy

#endif /* BUTTON_H */
