#include <Box2D/Dynamics/b2Body.h>

#include <iostream>

#include "Entity/CircleEntity.hpp"
#include "Entity/Entity.hpp"
#include "Entity/RectangleEntity.hpp"
#include "World/World.hpp"
#include "util/converter.hpp"

namespace foggy {
World::World(const sf::Vector2f &gravity)
    : b2World(b2Vec2(gravity.x, gravity.y)) {}

void World::Update(const sf::Time &delta_time) {
    while (!m_entities.empty() && !m_entities.top()->IsAlive()) {
        DestroyBody(m_entities.top()->GetB2BodyRef());
        m_entities.pop();
    }
    Step(delta_time.asSeconds(), 8, 3);
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const b2Body *body = GetBodyList(); body != nullptr;
         body = body->GetNext()) {
        Entity *entity = static_cast<Entity *>(body->GetUserData());

        /* The World cooridate system is right-handed, i.e. Y+ is up and X+ is
         * right. The Screen cooridate system is left-handede, i.e. Y+ is down
         * and X+ is right.
         * Here, we convert World cooridate to Screen coordinate.*/
        sf::Vector2f position(converter::MetersToPixels(body->GetPosition().x),
                              target.getSize().y - converter::MetersToPixels(
                                                       body->GetPosition().y));
        float rotation = -converter::RadToDeg<float>(body->GetAngle());
        if (entity != nullptr) {
            entity->GetShape()->setPosition(position);
            entity->GetShape()->setRotation(rotation);

            sf::Shape *shape = entity->GetShape();
            target.draw(*shape, states);
        }
    }
}

void World::SpawnCollidableEntity(Entity::Ptr entity, b2BodyType type) {
    m_entities.push(entity);
    entity->CreateB2Body(*this, type);
}

}  // namespace foggy
