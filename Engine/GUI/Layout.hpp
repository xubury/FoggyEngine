#ifndef LAYOUT_H
#define LAYOUT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

#include "GUI/Widget.hpp"

namespace foggy {
namespace gui {

class Layout : virtual protected Widget {
   public:
    Layout(Widget *parent = nullptr);
    virtual ~Layout() = default;

    void setSpace(float pixel);

    virtual void clear() = 0;

   protected:
    friend class Container;
    friend class Frame;
    float m_space;
    sf::RectangleShape m_shape;
};

}  // namespace gui
}  // namespace foggy

#endif /* LAYOUT_H */
