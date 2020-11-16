#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
namespace foggy {

/** Design idea:
 * Think of Entity as a hitbox stuff.
 * So we can attach sprite etc to it. */
class Entity {
   public:
    using Ptr = std::shared_ptr<Entity>;

    using ShapePtr = std::unique_ptr<sf::Shape>;

    enum class Type { Rectangle, Circle };

    template <typename T>
    static bool CheckType(Entity *entity);

   public:
    Entity(ShapePtr shape, b2BodyType type);

    virtual ~Entity() = 0;

    sf::Shape *GetShape() const;

    b2BodyType GetType() const;

   protected:
    void SetShape(std::unique_ptr<sf::Shape> shape);

   private:
    b2BodyType m_b2_type;

    std::unique_ptr<sf::Shape> m_shape;
};

inline Entity::~Entity() = default;

inline sf::Shape *Entity::GetShape() const { return m_shape.get(); }

inline b2BodyType Entity::GetType() const { return m_b2_type; }

inline void Entity::SetShape(std::unique_ptr<sf::Shape> shape) {
    m_shape = std::move(shape);
}

template <typename T>
inline bool Entity::CheckType(Entity *entity) {
    static_assert(std::is_base_of<Entity, T>::value,
                  "T muse be derived from Entity!");
    return dynamic_cast<T *>(entity) != nullptr;
}

} /* namespace foggy */

#endif /* ENTITY_H */
