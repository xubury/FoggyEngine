#ifndef RECTANGLEENTITY_H
#define RECTANGLEENTITY_H

#include "Entity.hpp"
#include "util/converter.hpp"
namespace foggy {

class RectangleEntity : public Entity {
   public:
    static std::shared_ptr<RectangleEntity> Create(const sf::Vector2f &pos,
                                       const sf::Vector2f &size,
                                       b2BodyType type);

   public:
    RectangleEntity(const sf::Vector2f &pos, const sf::Vector2f &size,
                    b2BodyType type);
    void UpdateRenderStatus() override;

   private:
};

inline std::shared_ptr<RectangleEntity> RectangleEntity::Create(const sf::Vector2f &pos,
                                                    const sf::Vector2f &size,
                                                    b2BodyType type) {
    std::shared_ptr<RectangleEntity> entity(new RectangleEntity(pos, size, type));
    return entity;
}

}  // namespace foggy

#endif /* RECTANGLEENTITY_H */
