#include <Box2D/Dynamics/b2Body.h>

#include <iostream>

#include "Entity/CircleEntity.hpp"
#include "Entity/Entity.hpp"
#include "Entity/RectangleEntity.hpp"
#include "GameWorld.hpp"
#include "util/converter.hpp"

namespace foggy {
GameWorld::GameWorld(const sf::Vector2f &gravity)
    : b2World(b2Vec2(gravity.x, gravity.y)) {}

void GameWorld::Update(const sf::Time &delta_time) {
    while (!m_entities.empty() && !m_entities.top()->IsAlive()) {
        DestroyBody(m_entities.top()->GetB2BodyRef());
        m_entities.pop();
    }
    Step(delta_time.asSeconds(), 8, 3);
}

void GameWorld::RenderOn(sf::RenderWindow &window) {
    for (b2Body *body = GetBodyList(); body != nullptr;
         body = body->GetNext()) {
        Entity *entity = static_cast<Entity *>(body->GetUserData());

        /* The World cooridate system is right-handed, i.e. Y+ is up and X+ is
         * right. The Screen cooridate system is left-handede, i.e. Y+ is down
         * and X+ is right.
         * Here, we convert World cooridate to Screen coordinate.*/
        sf::Vector2f position(converter::MetersToPixels(body->GetPosition().x),
                              window.getSize().y - converter::MetersToPixels(
                                                       body->GetPosition().y));
        float rotation = -converter::RadToDeg<float>(body->GetAngle());
        if (entity != nullptr) {
            entity->GetShape()->setPosition(position);
            entity->GetShape()->setRotation(rotation);

            sf::Shape *shape = entity->GetShape();
            window.draw(*shape);
        }
    }
}

void GameWorld::SpawnEntity(Entity::Ptr entity) {
    if (entity->IsPersistent())
        m_persistant_entities.push_back(entity);
    else
        m_entities.push(entity);

    b2BodyDef body_def;
    sf::Vector2f pos = entity->GetShape()->getPosition();
    body_def.position.Set(converter::PixelsToMeters<float>(pos.x),
                          converter::PixelsToMeters<float>(pos.y));
    body_def.type = entity->GetType();
    std::unique_ptr<b2Shape> b2_shape;
    if (Entity::CheckType<RectangleEntity>(entity.get())) {
        b2_shape = CreateShape(entity, Entity::Type::Rectangle);

    } else if (Entity::CheckType<CircleEntity>(entity.get())) {
        b2_shape = CreateShape(entity, Entity::Type::Circle);
    }

    b2FixtureDef fixture_def;
    fixture_def.density = 1.0;
    fixture_def.friction = 0.4;
    fixture_def.restitution = 0.5;
    fixture_def.shape = b2_shape.get();

    b2Body *res = CreateBody(&body_def);
    res->CreateFixture(&fixture_def);
    res->SetUserData(entity.get());
    entity->SetB2BodyRef(res);
}

std::unique_ptr<b2Shape> GameWorld::CreateShape(Entity::Ptr entity,
                                                Entity::Type type) {
    std::unique_ptr<b2Shape> b2_shape;
    switch (type) {
        case Entity::Type::Rectangle: {
            b2_shape = std::make_unique<b2PolygonShape>();
            sf::FloatRect rect = entity->GetShape()->getLocalBounds();
            dynamic_cast<b2PolygonShape *>(b2_shape.get())
                ->SetAsBox(converter::PixelsToMeters<float>(rect.width / 2.0),
                           converter::PixelsToMeters<float>(rect.height / 2.0));
            break;
        }
        case Entity::Type::Circle: {
            b2_shape = std::make_unique<b2CircleShape>();
            dynamic_cast<b2CircleShape *>(b2_shape.get())->m_radius =
                converter::PixelsToMeters<float>(
                    dynamic_cast<sf::CircleShape *>(entity->GetShape())
                        ->getRadius());
            break;
        }
        default: {
            std::cerr << "undefined type" << std::endl;
            break;
        }
    }
    return b2_shape;
}

}  // namespace foggy
