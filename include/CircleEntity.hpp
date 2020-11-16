#ifndef CIRCLEENTITY_H
#define CIRCLEENTITY_H

#include <SFML/Graphics/CircleShape.hpp>

#include "Entity.hpp"

namespace foggy {

class CircleEntity : public Entity {
   public:
    static CircleEntity::Ptr Create(const sf::Vector2f &pos, float radius,
                                    b2BodyType type, const sf::Time &life_time);

   public:
    CircleEntity(const sf::Vector2f &pos, float radius, b2BodyType type,
                 const sf::Time &life_time);

   private:
};

inline CircleEntity::Ptr CircleEntity::Create(const sf::Vector2f &pos,
                                              float radius, b2BodyType type,
                                              const sf::Time &life_time) {
    CircleEntity::Ptr entity(new CircleEntity(pos, radius, type, life_time));
    return entity;
}

}  // namespace foggy

#endif /* CIRCLEENTITY_H */
