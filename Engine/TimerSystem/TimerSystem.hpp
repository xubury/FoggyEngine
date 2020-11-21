#ifndef TIMERSYSTEM_H
#define TIMERSYSTEM_H

#include <functional>
#include <SFML/System/Clock.hpp>
#include "util/PriorityQueue.hpp"

namespace foggy {
namespace ts {

struct Timer {
public:
    using FuncType = std::function<void()>;

    Timer(const sf::Time &life_time, FuncType callback);

    bool IsTimeUp() const;

    sf::Time GetRemainingTime() const;

    struct LessRemainingTime {
        bool operator()(const Timer &lhs, const Timer &rhs) const;
    };

    struct GreaterRemainingTime {
        bool operator()(const Timer &lhs, const Timer &rhs) const;
    };

    void Invoke() const;

    void Restart();

private:
    sf::Clock m_spawn_timer;
    sf::Time m_life_time;
    FuncType m_callback;
};

class TimerSystem {
   public:
    void Update();

    void AddTimer(const sf::Time &time, const Timer::FuncType &callback);

   private:
    PriorityQueue<Timer, std::vector<Timer>, Timer::LessRemainingTime> m_queue;
};

}  // namespace es
}  // namespace foggy

#endif /* TIMERSYSTEM_H */
