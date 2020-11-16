#include <Entity.hpp>

namespace foggy {

const sf::Time Entity::PERSISTANT = sf::seconds(0);

Entity::Entity(ShapePtr shape, b2BodyType type, const sf::Time &life_time)
    : m_shape(std::move(shape)),
      m_life_time(life_time),
      m_b2_type(type),
      m_b2_body_ref(nullptr) {
    m_spawn_timer.restart();
    m_shape->setFillColor(sf::Color::Transparent);
    m_shape->setOutlineColor(sf::Color::Green);
    m_shape->setOutlineThickness(1.f);
}

bool Entity::LessRemainingTime::operator()(const Entity::Ptr &lhs,
                                           const Entity::Ptr &rhs) const {
    return lhs->GetRemainingTime() < rhs->GetRemainingTime();
}
bool Entity::GreaterRemainingTime::operator()(const Entity::Ptr &lhs,
                                              const Entity::Ptr &rhs) const {
    return lhs->GetRemainingTime() > rhs->GetRemainingTime();
}

Entity::~Entity() = default;

sf::Shape *Entity::GetShape() const { return m_shape.get(); }

b2BodyType Entity::GetType() const { return m_b2_type; }

void Entity::SetShape(std::unique_ptr<sf::Shape> shape) {
    m_shape = std::move(shape);
}

bool Entity::IsAlive() const {
    if (IsPersistent()) {
        return true;
    } else
        return m_spawn_timer.getElapsedTime() < m_life_time;
}

bool Entity::IsPersistent() const { return m_life_time == PERSISTANT; }

sf::Time Entity::GetRemainingTime() const {
    return m_life_time - m_spawn_timer.getElapsedTime();
}

void Entity::SetB2BodyRef(b2Body *ref) { m_b2_body_ref = ref; }

b2Body *Entity::GetB2BodyRef() { return m_b2_body_ref; }

}  // namespace foggy
