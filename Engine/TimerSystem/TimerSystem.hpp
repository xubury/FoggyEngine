#ifndef TIMERSYSTEM_HPP
#define TIMERSYSTEM_HPP

#include <SFML/System/Clock.hpp>
#include <functional>

#include "Utils/PriorityQueue.hpp"

namespace foggy {
namespace ts {

struct Timer {
   public:
    using FuncType = std::function<void()>;

    Timer(const sf::Time &life_time, FuncType callback);

    bool isTimeUp() const;

    sf::Time getRemainingTime() const;

    struct LessRemainingTime {
        bool operator()(const Timer &lhs, const Timer &rhs) const;
    };

    struct GreaterRemainingTime {
        bool operator()(const Timer &lhs, const Timer &rhs) const;
    };

    void invoke() const;

    void restart();

   private:
    sf::Clock m_spawn_timer;
    sf::Time m_life_time;
    FuncType m_callback;
};

class TimerSystem {
   public:
    void update();

    void addTimer(const sf::Time &time, const Timer::FuncType &callback);

   private:
    PriorityQueue<Timer, std::vector<Timer>, Timer::LessRemainingTime> m_queue;
};

}  // namespace ts
}  // namespace foggy

#endif /* TIMERSYSTEM_HPP */
