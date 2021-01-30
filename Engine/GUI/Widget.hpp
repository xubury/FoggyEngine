#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
namespace foggy {
namespace gui {

class Widget : public sf::Drawable {
   public:
    Widget(Widget *parent = nullptr);
    virtual ~Widget() = default;

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &pos);

    sf::Vector2f getPosition() const;
    virtual sf::Vector2f getSize() const = 0;

    void hide();
    bool isHidden() const;
    void show();
    bool isVisible() const;
    void toggle();

   protected:
    friend class Container;
    friend class VLayout;
    virtual bool processEvent(const sf::Event &event,
                              const sf::Vector2f &parent_pos);
    virtual void processEvents(const sf::Vector2f &parent_pos);
    virtual void updateShape();

    Widget *m_parent;
    sf::Vector2f m_pos;
    bool m_is_visible;
};

}  // namespace gui
}  // namespace foggy

#endif /* WIDGET_H */
