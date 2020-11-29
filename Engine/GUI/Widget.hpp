#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
namespace foggy {

class Widget : public sf::Drawable {
   public:
    Widget(Widget *parent = nullptr);
    virtual ~Widget() = default;

    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f &pos);

    sf::Vector2f GetPosition() const;
    virtual sf::Vector2f GetSize() const = 0;

   protected:
    friend class Container;
    friend class VLayout;
    virtual bool ProcessEvent(const sf::Event &event,
                              const sf::Vector2f &parent_pos);
    virtual void ProcessEvents(const sf::Vector2f &parent_pos);
    virtual void UpdateShape();

    Widget *m_parent;
    sf::Vector2f m_pos;
};
}  // namespace foggy

#endif /* WIDGET_H */
