#ifndef ACTIONMAP_HPP
#define ACTIONMAP_HPP

#include <unordered_map>

#include "ActionSystem/Action.hpp"

namespace foggy {

template <typename T = int>
class ActionMap {
   public:
    ActionMap() = default;
    ActionMap(const ActionMap<T> &) = delete;
    ActionMap<T> &operator=(const ActionMap<T> &) = delete;

    void map(const T &key, const Action &action);
    const Action &get(const T &key) const;

   private:
    std::unordered_map<T, Action> m_map;
};

template <typename T>
void ActionMap<T>::map(const T &key, const Action &action) {
    m_map.emplace(key, action);
}

template <typename T>
const Action &ActionMap<T>::get(const T &key) const {
    return m_map.at(key);
}

}  // namespace foggy

#endif /* ACTIONMAP_HPP */
