#ifndef ACTIONTARGET_HPP
#define ACTIONTARGET_HPP

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

    bool processEvent(const sf::Event &event) const;
    void processEvents() const;

    void bind(const T &key, const FuncType &callback);
    void bind(const Action &action, const FuncType &callback);
    void bind(Action &&action, const FuncType &callback);
    void unbind(const T &key);

   private:
    std::list<ActionPair> m_event_realtime;
    std::list<ActionPair> m_event_poll;
    std::list<std::pair<Action, FuncType>> m_event_realtime_action;
    std::list<std::pair<Action, FuncType>> m_event_poll_action;

    const ActionMap<T> &m_action_map;
};

template <typename T>
ActionTarget<T>::ActionTarget(const ActionMap<T> &map) : m_action_map(map) {}

template <typename T>
bool ActionTarget<T>::processEvent(const sf::Event &event) const {
    for (const auto &pair : m_event_poll_action) {
        if (pair.first == event) {
            pair.second(event);  // invoke callback
            return true;
        }
    }
    for (const auto &pair : m_event_poll) {
        if (m_action_map.get(pair.first) == event) {
            pair.second(event);  // invoke callback
            return true;
        }
    }
    return false;
}

template <typename T>
void ActionTarget<T>::processEvents() const {
    for (const auto &pair : m_event_realtime_action) {
        if (pair.first.test()) {
            pair.second(pair.first.m_event);  // invoke callback
        }
    }
    for (const ActionPair &pair : m_event_realtime) {
        const Action &action = m_action_map.get(pair.first);
        if (action.test()) {
            pair.second(action.m_event);  // invoke callback
        }
    }
}

template <typename T>
void ActionTarget<T>::bind(const T &key, const FuncType &callback) {
    const Action &action = m_action_map.get(key);
    if (action.m_type & Action::Type::RealTime) {
        m_event_realtime.emplace_back(key, callback);
    } else {
        m_event_poll.emplace_back(key, callback);
    }
}

template <typename T>
void ActionTarget<T>::bind(const Action &action, const FuncType &callback) {
    if (action.m_type & Action::Type::RealTime)
        m_event_realtime_action.emplace_back(action, callback);
    else
        m_event_poll_action.emplace_back(action, callback);
}

template <typename T>
void ActionTarget<T>::bind(Action &&action, const FuncType &callback) {
    if (action.m_type & Action::Type::RealTime)
        m_event_realtime_action.emplace_back(std::move(action), callback);
    else
        m_event_poll_action.emplace_back(std::move(action), callback);
}

template <typename T>
void ActionTarget<T>::unbind(const T &key) {
    const Action &action = m_action_map.get(key);
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

#endif /* ACTIONTARGET_HPP */
