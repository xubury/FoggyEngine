#include "TimerSystem/TimerSystem.hpp"

namespace foggy {
namespace ts {

Timer::Timer(const sf::Time &life_time, FuncType callback)
    : m_life_time(life_time), m_callback(std::move(callback)) {}

bool Timer::IsTimeUp() const { return GetRemainingTime() <= sf::seconds(0); }

sf::Time Timer::GetRemainingTime() const {
    return m_life_time - m_spawn_timer.getElapsedTime();
}

bool Timer::LessRemainingTime::operator()(const Timer &lhs,
                                          const Timer &rhs) const {
    return lhs.GetRemainingTime() > rhs.GetRemainingTime();
}

bool Timer::GreaterRemainingTime::operator()(const Timer &lhs,
                                             const Timer &rhs) const {
    return lhs.GetRemainingTime() > rhs.GetRemainingTime();
}

void Timer::Invoke() const { m_callback(); }

void Timer::Restart() { m_spawn_timer.restart(); }

void TimerSystem::Update() {
    while (!m_queue.empty() && m_queue.top().IsTimeUp()) {
        m_queue.top().Invoke();
        m_queue.pop();
    }
}

void TimerSystem::AddTimer(const sf::Time &time,
                           const Timer::FuncType &callback) {
    m_queue.emplace(time, callback);
}

}  // namespace ts
}  // namespace foggy
