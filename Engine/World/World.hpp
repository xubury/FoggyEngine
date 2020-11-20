#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <Box2D/Dynamics/b2World.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "Camera/Camera.hpp"
#include "Entity/Entity.hpp"
#include "util/PriorityQueue.hpp"

namespace foggy {

/* The World cooridate system is right-handed, i.e. Y+ is up and X+ is
 * right. The Screen cooridate system is left-handed, i.e. Y+ is down
 * and X+ is right. So everything inside GameWorld is in World Coordinate
 * System. The Render function will convert World coordinate to Screen
 * coordinate. */
class World : public b2World, public sf::Drawable {
   public:
    World(const sf::Vector2f &gravity = sf::Vector2f(0.f, 9.8f));

    void Update(const sf::Time &delta_time);

    /* Draw all entities in this world */
    void draw(sf::RenderTarget &target,
              sf::RenderStates states = sf::RenderStates::Default) const;

    /* Spawn a collidable entity with the one of the type in b2BodyType. */
    void SpawnCollidableEntity(const Entity::Ptr &entity, b2BodyType type);

    void DestroyEntity(const Entity::Ptr &entity);

    Camera &GetCamera();

   private:
    PriorityQueue<Entity::Ptr, std::vector<Entity::Ptr>,
                  Entity::GreaterRemainingTime>
        m_entities;

    Camera m_camera;
};

} /* namespace foggy */

#endif /* GAMEWORLD_H */
