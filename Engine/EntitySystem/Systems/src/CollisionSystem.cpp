#include <sol/sol.hpp>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/Transform.hpp"
#include "EntitySystem/Systems/CollisionSystem.hpp"

namespace foggy {
namespace es {
CollisionSystem::CollisionSystem(float x, float y) : b2World(b2Vec2(x, y)) {}

void CollisionSystem::Update(es::EntityManager<es::DefaultEntity> &manager,
                             const sf::Time &delta_time) {
    Step(delta_time.asSeconds(), 8, 3);
    component::Collision::Handle collision;
    auto view = manager.GetByComponents(collision);
    auto cur = view.Begin();
    auto end = view.End();
    for (; cur != end; ++cur) {
        b2Body *body = collision->b2body_ref;
        b2Vec2 pos(body->GetPosition());
        pos.x = converter::MetersToPixels(pos.x);
        pos.y = converter::MetersToPixels(pos.y);
        float angle = converter::RadToDeg(body->GetAngle());
        cur->Component<component::Transform>()->SetPosition(pos.x, pos.y);
        cur->Component<component::Transform>()->SetRotation(angle);
    }
}

LuaCollision::LuaCollision(SystemManager<es::DefaultEntity> *manager,
                           const std::string &filename)
    : m_world(nullptr) {
    sol::state lua;
    lua.script_file(filename);

    sol::object system = lua["CollisionSystem"];
    if (system.is<sol::table>()) {
        sol::table system_table = system;
        std::cout << "adding collision system" << std::endl;
        float x = system_table["x"];
        float y = system_table["y"];
        manager->Add<foggy::es::CollisionSystem>(x, y);
        m_world = manager->System<es::CollisionSystem>();
    }
}

void LuaCollision::InitComponent(es::EntityManager<es::DefaultEntity> *manager,
                                 int id, const std::string &filename) {
    assert(m_world != nullptr);
    sol::state lua;
    lua.script_file(filename);
    sol::object comp = lua["CompCollision"];
    if (comp.is<sol::table>()) {
        sol::table comp_table = comp;
        b2BodyDef body_def;
        body_def.type = comp_table["body_type"];
        body_def.fixedRotation = comp_table["fix_angle"];

        component::Collision::Handle collision =
            manager->AddComponent<component::Collision>(id, m_world, body_def);
        std::cout << "Comp Collision Added" << std::endl;
        sol::table fixture_table = comp_table["fixtures"];
        for (const auto &pair : fixture_table) {
            sol::table fixture = pair.second;
            std::string shape = fixture["shape"];
            if (shape == "Polygon") {
                PopulatePolygonFixture(fixture, collision.Get());
            } else if (shape == "Circle") {
                PopulateCircleFixture(fixture, collision.Get());
            }
        }
    }
}

void LuaCollision::PopulatePolygonFixture(sol::table &table,
                                          component::Collision *collision) {
    sol::table vertices_table = table["vertices"];
    std::vector<b2Vec2> vertices;
    for (const auto &pair : vertices_table) {
        sol::table pos = pair.second;
        float x = pos["x"];
        float y = pos["y"];
        vertices.emplace_back(converter::PixelsToMeters(x),
                              converter::PixelsToMeters(y));
    }

    b2PolygonShape b2shape;
    b2shape.Set(vertices.data(), vertices.size());
    b2FixtureDef fixture_def;
    fixture_def.density = table["density"];
    fixture_def.friction = table["friction"];
    fixture_def.restitution = table["restitution"];
    fixture_def.shape = &b2shape;
    collision->AddFixture(fixture_def);
}

void LuaCollision::PopulateCircleFixture(sol::table &table,
                                         component::Collision *collision) {
    b2CircleShape b2shape;
    float radius = table["radius"];
    b2shape.m_radius = converter::PixelsToMeters(radius);
    b2FixtureDef fixture_def;
    fixture_def.density = table["density"];
    fixture_def.friction = table["friction"];
    fixture_def.restitution = table["restitution"];
    fixture_def.shape = &b2shape;
    collision->AddFixture(fixture_def);
}

}  // namespace es
}  // namespace foggy
