#include <Box2D/Dynamics/b2Body.h>

#include "Entity.hpp"
#include "GameWorld.hpp"
#include "RectangleEntity.hpp"
#include "util/converter.hpp"

namespace foggy {
GameWorld::GameWorld(const sf::Vector2f &gravity)
    : b2World(b2Vec2(gravity.x, gravity.y)) {}

void GameWorld::RenderOn(sf::RenderWindow &window) {
    for (b2Body *body = GetBodyList(); body != nullptr;
         body = body->GetNext()) {
        Entity *entity = static_cast<Entity *>(body->GetUserData());
        sf::Vector2f position(converter::MetersToPixels(body->GetPosition().x),
                              converter::MetersToPixels(body->GetPosition().y));
        float rotation = converter::RadToDeg<float>(body->GetAngle());
        if (entity != nullptr) {
            entity->GetShape()->setPosition(position);
            entity->GetShape()->setRotation(rotation);

            sf::Shape *shape = entity->GetShape();
            window.draw(*shape);
        }
    }
}

void GameWorld::SpawnEntity(Entity::Ptr entity) {
    b2BodyDef body_def;
    sf::Vector2f pos = entity->GetShape()->getPosition();
    body_def.position.Set(converter::PixelsToMeters<float>(pos.x),
                          converter::PixelsToMeters<float>(pos.y));
    body_def.type = entity->GetType();
    b2PolygonShape b2_shape;
    sf::FloatRect rect = entity->GetShape()->getLocalBounds();
    b2_shape.SetAsBox(converter::PixelsToMeters<float>(rect.width / 2.0),
                      converter::PixelsToMeters<float>(rect.height / 2.0));

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.4;
    fixture_def.restitution = 0.5;
    fixture_def.shape = &b2_shape;

    b2Body *res = CreateBody(&body_def);
    res->CreateFixture(&fixture_def);
    res->SetUserData(entity.get());
    m_entites.push_back(entity);
}

}  // namespace foggy
