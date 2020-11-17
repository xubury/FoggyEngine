#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <Box2D/Dynamics/b2World.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <queue>

#include "Entity/Entity.hpp"

namespace foggy {

class GameWorld : public b2World {
   public:
    GameWorld(const sf::Vector2f &gravity = sf::Vector2f(0.f, 9.8f));

    void Update(const sf::Time &delta_time);

    void RenderOn(sf::RenderWindow &window);

    void SpawnEntity(Entity::Ptr entity);

   private:
    std::unique_ptr<b2Shape> CreateShape(Entity::Ptr entity, Entity::Type type);

    std::priority_queue<Entity::Ptr, std::vector<Entity::Ptr>,
                        Entity::GreaterRemainingTime>
        m_entities;
    std::vector<Entity::Ptr> m_persistant_entities;
};

} /* namespace foggy */

#endif /* GAMEWORLD_H */
