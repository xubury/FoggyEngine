#ifndef CIRCLEENTITY_H
#define CIRCLEENTITY_H

#include <SFML/Graphics/CircleShape.hpp>

#include "Entity.hpp"

namespace foggy {

class CircleEntity : public Entity {
   public:
    static CircleEntity::Ptr Create(const sf::Vector2f &pos, float radius,
                                    b2BodyType type);

   public:
    CircleEntity(const sf::Vector2f &pos, float radius, b2BodyType type);

   private:
};

inline CircleEntity::Ptr CircleEntity::Create(const sf::Vector2f &pos,
                                              float radius, b2BodyType type) {
    CircleEntity::Ptr entity(new CircleEntity(pos, radius, type));
    return entity;
}

}  // namespace foggy

#endif /* CIRCLEENTITY_H */
