#ifndef RECTANGLEENTITY_H
#define RECTANGLEENTITY_H

#include "Entity/Entity.hpp"
#include "util/converter.hpp"
namespace foggy {

class RectangleEntity : public Entity {
   public:
    static RectangleEntity::Ptr Create(const sf::Vector2f &pos,
                                       const sf::Vector2f &size,
                                       const sf::Time &life_time);

   public:
    RectangleEntity(const sf::Vector2f &pos, const sf::Vector2f &size,
                    const sf::Time &life_time);

    Type GetType() override;

   private:
    std::unique_ptr<b2Shape> CreateB2Shape() override;
};

inline RectangleEntity::Ptr RectangleEntity::Create(const sf::Vector2f &pos,
                                                    const sf::Vector2f &size,
                                                    const sf::Time &life_time) {
    RectangleEntity::Ptr entity(new RectangleEntity(pos, size, life_time));
    return entity;
}

} /* namespace foggy */

#endif /* RECTANGLEENTITY_H */
