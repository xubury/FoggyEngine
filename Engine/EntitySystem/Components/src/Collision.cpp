#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

namespace foggy {
namespace component {

Collision::Collision(es::CollisionSystem &world, b2BodyDef &def, bool debug)
    : debug(debug) {
    b2body_ref = world.CreateBody(&def);
}

void Collision::AddFixture(const b2FixtureDef &fixture) {
    b2Shape::Type type = fixture.shape->GetType();
    if (type == b2Shape::Type::e_circle) {
        const b2CircleShape *circle =
            static_cast<const b2CircleShape *>(fixture.shape);
        debug_shape.emplace_back(std::make_unique<sf::CircleShape>(
            converter::MetersToPixels(circle->m_radius)));
        debug_shape.back()->setOrigin(
            sf::Vector2f(converter::MetersToPixels(circle->m_radius),
                         converter::MetersToPixels(circle->m_radius)));
    } else if (type == b2Shape::Type::e_polygon) {
        const b2PolygonShape *rect =
            static_cast<const b2PolygonShape *>(fixture.shape);
        debug_shape.emplace_back(std::make_unique<sf::ConvexShape>());
        sf::ConvexShape *convex =
            static_cast<sf::ConvexShape *>(debug_shape.back().get());
        convex->setPointCount(rect->GetVertexCount());
        for (int i = 0; i < rect->GetVertexCount(); ++i) {
            b2Vec2 pt = rect->GetVertex(i);
            convex->setPoint(i, sf::Vector2f(converter::MetersToPixels(pt.x),
                                             converter::MetersToPixels(pt.y)));
        }
        convex->setOrigin(converter::MetersToPixels(rect->m_centroid.x),
                          converter::MetersToPixels(rect->m_centroid.y));
    }
    debug_shape.back()->setFillColor(sf::Color::Transparent);
    debug_shape.back()->setOutlineColor(sf::Color::Green);
    debug_shape.back()->setOutlineThickness(1.0);
    b2body_ref->CreateFixture(&fixture);
}

Collision::~Collision() { b2body_ref->GetWorld()->DestroyBody(b2body_ref); }
}  // namespace component
}  // namespace foggy
