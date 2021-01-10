#ifndef ACTION_H
#define ACTION_H

#include <SFML/Window/Event.hpp>

namespace foggy {

class Action {
   public:
    enum Type { RealTime = 1, Pressed = 1 << 1, Released = 1 << 2 };

    Action(const sf::Event::EventType &event);

    Action(const sf::Keyboard::Key &key,
           int type = Type::RealTime | Type::Pressed);

    Action(const sf::Mouse::Button &button,
           int type = Type::RealTime | Type::Pressed);

    bool test() const;

    bool operator==(const sf::Event &event) const;
    bool operator==(const Action &other) const;

   private:
    template <typename>
    friend class ActionTarget;

    sf::Event m_event;
    int m_type;
};

}  // namespace foggy

#endif /* ACTION_H */
