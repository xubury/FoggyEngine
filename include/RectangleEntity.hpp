#ifndef RECTANGLEENTITY_H
#define RECTANGLEENTITY_H

#include "Entity.hpp"
#include "util/converter.hpp"
namespace foggy {

class RectangleEntity : public Entity {
   public:
    static RectangleEntity::Ptr Create(const sf::Vector2f &pos,
                                       const sf::Vector2f &size,
                                       b2BodyType type);

   public:
    RectangleEntity(const sf::Vector2f &pos, const sf::Vector2f &size,
                    b2BodyType type);

   private:
};

inline RectangleEntity::Ptr RectangleEntity::Create(const sf::Vector2f &pos,
                                                    const sf::Vector2f &size,
                                                    b2BodyType type) {
    RectangleEntity::Ptr entity(new RectangleEntity(pos, size, type));
    return entity;
}

} /* namespace foggy */

#endif /* RECTANGLEENTITY_H */
