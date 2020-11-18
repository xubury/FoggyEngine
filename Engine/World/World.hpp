#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <Box2D/Dynamics/b2World.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <queue>

#include "Camera/Camera.hpp"
#include "Entity/Entity.hpp"

namespace foggy {

/* The World cooridate system is right-handed, i.e. Y+ is up and X+ is
 * right. The Screen cooridate system is left-handed, i.e. Y+ is down
 * and X+ is right. So everything inside GameWorld is in World Coordinate
 * System. The Render function will convert World coordinate to Screen
 * coordinate. */
class World : public b2World {
   public:
    World(const sf::Vector2f &gravity = sf::Vector2f(0.f, 9.8f));

    void Update(const sf::Time &delta_time);

    void RenderOn(sf::RenderWindow &window);

    void SpawnEntity(Entity::Ptr entity, b2BodyType type);

   private:
    std::priority_queue<Entity::Ptr, std::vector<Entity::Ptr>,
                        Entity::GreaterRemainingTime>
        m_entities;
    std::vector<Entity::Ptr> m_persistant_entities;
};

} /* namespace foggy */

#endif /* GAMEWORLD_H */
