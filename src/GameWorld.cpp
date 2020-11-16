#include <Box2D/Dynamics/b2Body.h>

#include <iostream>

#include "CircleEntity.hpp"
#include "Entity.hpp"
#include "GameWorld.hpp"
#include "RectangleEntity.hpp"
#include "util/converter.hpp"

namespace foggy {
GameWorld::GameWorld(const sf::Vector2f &gravity)
    : b2World(b2Vec2(gravity.x, gravity.y)) {}

void GameWorld::Update(const sf::Time &delta_time) {
    Step(delta_time.asSeconds(), 8, 3);
}

void GameWorld::RenderOn(sf::RenderWindow &window) {
    b2Body *body = GetBodyList();
    while (body != nullptr) {
        Entity *entity = static_cast<Entity *>(body->GetUserData());
        // TODO: Move this to Update
        if (!entity->IsAlive()) {
            b2Body *next = body->GetNext();
            m_entites.remove_if(
                [entity](const auto &v) -> bool { return v.get() == entity; });
            DestroyBody(body);
            body = next;
            continue;
        }

        sf::Vector2f position(converter::MetersToPixels(body->GetPosition().x),
                              converter::MetersToPixels(body->GetPosition().y));
        float rotation = converter::RadToDeg<float>(body->GetAngle());
        if (entity != nullptr) {
            entity->GetShape()->setPosition(position);
            entity->GetShape()->setRotation(rotation);

            sf::Shape *shape = entity->GetShape();
            window.draw(*shape);
        }
        body = body->GetNext();
    }
}

void GameWorld::SpawnEntity(Entity::Ptr entity) {
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
    m_entites.push_back(entity);
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
