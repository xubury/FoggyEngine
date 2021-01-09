#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

namespace foggy {
namespace component {

Collision::Collision(b2BodyDef &def, bool debug)
    : b2body_ref(nullptr), b2body_def(def), debug(debug) {}

Collision::~Collision() { b2body_ref->GetWorld()->DestroyBody(b2body_ref); }

void Collision::AddFixture(const b2FixtureDef &fixture) {
    if (b2body_ref == nullptr) {
        es::SystemManager<es::DefaultEntity> *systems = Manager()->GetSystems();
        assert(systems != nullptr);
        auto *world = systems->System<es::CollisionSystem>();
        assert(world != nullptr);
        b2body_ref = world->CreateBody(&b2body_def);
    }
    /* To stay consistency with the transform, we have to remove the
     * debug_shape's scale. Because the transform will be applied at drawing
     * stage. */
    Transform::Handle trans = Manager()->GetComponent<Transform>(OwnerID());
    sf::Vector2f scale = trans->getScale();
    b2Shape::Type type = fixture.shape->GetType();
    if (type == b2Shape::Type::e_circle) {
        const b2CircleShape *circle =
            static_cast<const b2CircleShape *>(fixture.shape);
        // FIXME: scale on  X Y should both be considered
        float radius = circle->m_radius / scale.x;
        debug_shape.emplace_back(std::make_unique<sf::CircleShape>(
            converter::MetersToPixels(radius)));
        debug_shape.back()->setOrigin(
            sf::Vector2f(converter::MetersToPixels(radius),
                         converter::MetersToPixels(radius)));
    } else if (type == b2Shape::Type::e_polygon) {
        const b2PolygonShape *rect =
            static_cast<const b2PolygonShape *>(fixture.shape);
        debug_shape.emplace_back(std::make_unique<sf::ConvexShape>());
        sf::ConvexShape *convex =
            static_cast<sf::ConvexShape *>(debug_shape.back().get());
        convex->setPointCount(rect->m_count);
        for (int i = 0; i < rect->m_count; ++i) {
            b2Vec2 pt = rect->m_vertices[i];
            convex->setPoint(
                i, sf::Vector2f(converter::MetersToPixels(pt.x / scale.x),
                                converter::MetersToPixels(-pt.y / scale.y)));
        }
    }
    debug_shape.back()->setFillColor(sf::Color::Transparent);
    debug_shape.back()->setOutlineColor(sf::Color::Green);
    debug_shape.back()->setOutlineThickness(1.0);
    b2body_ref->CreateFixture(&fixture);
}

}  // namespace component
}  // namespace foggy
