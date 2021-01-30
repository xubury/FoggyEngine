#ifndef CONTAINER_H
#define CONTAINER_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "GUI/Widget.hpp"

namespace foggy {
namespace gui {

class Layout;
class Container : virtual public Widget {
   public:
    Container(Widget* parent = nullptr);
    virtual ~Container();

    void setLayout(Layout* layout);
    Layout* getLayout() const;

    virtual sf::Vector2f getSize() const override;

    void clear();

    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);

   protected:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;

    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos) override;
    virtual void processEvents(const sf::Vector2f& parent_pos) override;

    virtual void updateShape() override;

   private:
    sf::RectangleShape m_shape;
    Layout* m_layout;
};

}  // namespace gui
}  // namespace foggy

#endif /* CONTAINER_H */
