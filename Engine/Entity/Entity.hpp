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
 * Then we can attach sprite etc to it. */
class Entity {
   public:
    static const sf::Time PERSISTANT;

    using Ptr = std::shared_ptr<Entity>;

    using ShapePtr = std::unique_ptr<sf::Shape>;

    enum class Type { Rectangle, Circle };

    /* Check if entity is a Type of T */
    template <typename T>
    static bool CheckType(Entity *entity);

   public:
    friend class GameWorld;

    Entity(ShapePtr shape, b2BodyType type, const sf::Time &life_time);

    virtual ~Entity() = 0;

    /* Check if entity is alive,
     * the destruction is handled by the user */
    bool IsAlive() const;

    /* Check if entity has a life time (life time != 0) */
    bool IsPersistent() const;

    /* Get the remaining time before entity reach its life span */
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

    b2BodyType GetType() const;

    void SetB2BodyRef(b2Body *ref);

    b2Body *GetB2BodyRef();

   private:
    /* The basic shape of entity. */
    ShapePtr m_shape;

    /* Timer that store how much time have passed since this entity spawned */
    sf::Clock m_spawn_timer;

    /* How much time this entity can live.
     * If the time is negative, then this object can live forever. */
    sf::Time m_life_time;

    /* The box2d type of this entity. */
    b2BodyType m_b2_type;

    /* The box2d body pointer that is binded with this entity. */
    b2Body *m_b2_body_ref;
};

template <typename T>
bool Entity::CheckType(Entity *entity) {
    static_assert(std::is_base_of<Entity, T>::value,
                  "T muse be derived from Entity!");
    return dynamic_cast<T *>(entity) != nullptr;
}

} /* namespace foggy */

#endif /* ENTITY_H */
