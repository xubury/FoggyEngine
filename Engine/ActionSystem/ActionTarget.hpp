#ifndef ACTIONTARGET_H
#define ACTIONTARGET_H

#include <functional>
#include <list>
#include <utility>

#include "ActionSystem/ActionMap.hpp"

namespace foggy {

template <typename T = int>
class ActionTarget {
   public:
    using FuncType = std::function<void(const sf::Event &)>;
    using ActionPair = std::pair<T, FuncType>;

   public:
    ActionTarget(const ActionTarget<T> &) = delete;
    ActionTarget<T> &operator=(const ActionTarget<T> &) = delete;

    ActionTarget(const ActionMap<T> &map);

    bool ProcessEvent(const sf::Event &event) const;
    void ProcessEvents() const;

    void Bind(const T &key, const FuncType &callback);
    void Unbind(const T &key);

   private:
    std::list<ActionPair> m_event_realtime;
    std::list<ActionPair> m_event_poll;

    const ActionMap<T> &m_action_map;
};

template <typename T>
ActionTarget<T>::ActionTarget(const ActionMap<T> &map) : m_action_map(map) {}

template <typename T>
bool ActionTarget<T>::ProcessEvent(const sf::Event &event) const {
    bool res = false;
    for (const ActionPair &pair : m_event_poll) {
        if (m_action_map.Get(pair.first) == event) {
            pair.second(event);  // invoke callback
            res = true;
            break;
        }
    }
    return res;
}

template <typename T>
void ActionTarget<T>::ProcessEvents() const {
    for (const ActionPair &pair : m_event_realtime) {
        const Action &action = m_action_map.Get(pair.first);
        if (action.Test()) {
            pair.second(action.m_event);  // invoke callback
        }
    }
}

template <typename T>
void ActionTarget<T>::Bind(const T &key, const FuncType &callback) {
    const Action &action = m_action_map.Get(key);
    if (action.m_type & Action::Type::RealTime) {
        m_event_realtime.emplace_back(key, callback);
    } else {
        m_event_poll.emplace_back(key, callback);
    }
}

template <typename T>
void ActionTarget<T>::Unbind(const T &key) {
    const Action &action = m_action_map.Get(key);
    auto removeFunc = [&key](const ActionPair &pair) -> bool {
        return pair.first == key;
    };
    if (action.m_type & Action::Type::RealTime) {
        m_event_realtime.remove_if(removeFunc);
    } else {
        m_event_poll.remove_if(removeFunc);
    }
}

}  // namespace foggy

#endif /* ACTIONTARGET_H */
