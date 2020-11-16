#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
namespace foggy {

/** Design idea:
 * Think of Entity as a hitbox stuff.
 * So we can attach sprite etc to it. */
class Entity {
   public:
    static const sf::Time PERSISTANT;
    using Ptr = std::shared_ptr<Entity>;

    using ShapePtr = std::unique_ptr<sf::Shape>;

    enum class Type { Rectangle, Circle };

    template <typename T>
    static bool CheckType(Entity *entity);

   public:
    friend class GameWorld;

    Entity(ShapePtr shape, b2BodyType type, const sf::Time &life_time);

    virtual ~Entity() = 0;

    bool IsAlive() const;

    bool IsPersistent() const;

    sf::Time GetRemainingTime() const;

    struct LessRemainingTime {
        bool operator()(const Entity::Ptr &lhs, const Entity::Ptr &rhs) const;
    };

    struct GreaterRemainingTime {
        bool operator()(const Entity::Ptr &lhs, const Entity::Ptr &rhs) const;
    };

   protected:
    void SetShape(std::unique_ptr<sf::Shape> shape);

    sf::Shape *GetShape() const;

   private:
    b2BodyType GetType() const;

    void SetB2BodyRef(b2Body *ref);

    b2Body *GetB2BodyRef();

   private:
    b2BodyType m_b2_type;

    std::unique_ptr<sf::Shape> m_shape;

    /* Timer that store how much time have passed
     * since this entity spawned */
    sf::Clock m_spawn_timer;

    /* How much time this entity can live.
     * If the time is negative, then this object can live forever. */
    sf::Time m_life_time;

    b2Body *m_b2_body_ref;
};

inline bool Entity::LessRemainingTime::operator()(
    const Entity::Ptr &lhs, const Entity::Ptr &rhs) const {
    return lhs->GetRemainingTime() < rhs->GetRemainingTime();
}
inline bool Entity::GreaterRemainingTime::operator()(
    const Entity::Ptr &lhs, const Entity::Ptr &rhs) const {
    return lhs->GetRemainingTime() > rhs->GetRemainingTime();
}

inline Entity::~Entity() = default;

inline sf::Shape *Entity::GetShape() const { return m_shape.get(); }

inline b2BodyType Entity::GetType() const { return m_b2_type; }

inline void Entity::SetShape(std::unique_ptr<sf::Shape> shape) {
    m_shape = std::move(shape);
}

inline bool Entity::IsAlive() const {
    if (IsPersistent()) {
        return true;
    } else
        return m_spawn_timer.getElapsedTime() < m_life_time;
}

inline bool Entity::IsPersistent() const { return m_life_time == PERSISTANT; }

inline sf::Time Entity::GetRemainingTime() const {
    return m_life_time - m_spawn_timer.getElapsedTime();
}

inline void Entity::SetB2BodyRef(b2Body *ref) { m_b2_body_ref = ref; }

inline b2Body *Entity::GetB2BodyRef() { return m_b2_body_ref; }

template <typename T>
inline bool Entity::CheckType(Entity *entity) {
    static_assert(std::is_base_of<Entity, T>::value,
                  "T muse be derived from Entity!");
    return dynamic_cast<T *>(entity) != nullptr;
}

} /* namespace foggy */

#endif /* ENTITY_H */
