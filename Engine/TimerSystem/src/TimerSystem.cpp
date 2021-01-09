#include "TimerSystem/TimerSystem.hpp"

namespace foggy {
namespace ts {

Timer::Timer(const sf::Time &life_time, FuncType callback)
    : m_life_time(life_time), m_callback(std::move(callback)) {}

bool Timer::isTimeUp() const { return getRemainingTime() <= sf::seconds(0); }

sf::Time Timer::getRemainingTime() const {
    return m_life_time - m_spawn_timer.getElapsedTime();
}

bool Timer::LessRemainingTime::operator()(const Timer &lhs,
                                          const Timer &rhs) const {
    return lhs.getRemainingTime() > rhs.getRemainingTime();
}

bool Timer::GreaterRemainingTime::operator()(const Timer &lhs,
                                             const Timer &rhs) const {
    return lhs.getRemainingTime() > rhs.getRemainingTime();
}

void Timer::invoke() const { m_callback(); }

void Timer::restart() { m_spawn_timer.restart(); }

void TimerSystem::update() {
    while (!m_queue.empty() && m_queue.top().isTimeUp()) {
        m_queue.top().invoke();
        m_queue.pop();
    }
}

void TimerSystem::addTimer(const sf::Time &time,
                           const Timer::FuncType &callback) {
    m_queue.emplace(time, callback);
}

}  // namespace ts
}  // namespace foggy
