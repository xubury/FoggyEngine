#ifndef CIRCLEENTITY_H
#define CIRCLEENTITY_H

#include <SFML/Graphics/CircleShape.hpp>

#include "Entity/Entity.hpp"

namespace foggy {

class CircleEntity : public Entity {
   public:
    static CircleEntity::Ptr Create(const sf::Vector2f &pos, float radius,
                                    const sf::Time &life_time);

   public:
    CircleEntity(const sf::Vector2f &pos, float radius,
                 const sf::Time &life_time);

    Type GetType() override;

   private:
    void CreateB2Body(b2World &world, b2BodyType type) override;
};

inline CircleEntity::Ptr CircleEntity::Create(const sf::Vector2f &pos,
                                              float radius,
                                              const sf::Time &life_time) {
    CircleEntity::Ptr entity(new CircleEntity(pos, radius, life_time));
    return entity;
}

}  // namespace foggy

#endif /* CIRCLEENTITY_H */
