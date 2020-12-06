#include <Box2D/Box2D.h>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/LuaScript.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "util/converter.hpp"
namespace foggy {
namespace component {

void LuaScript::InitScript(const std::string &filename) {
    lua.open_libraries();
    lua.script_file(filename);
    InitComponent();
}

void LuaScript::InitComponent() {
    InitCollision();
    InitSkin();
}

void LuaScript::InitCollision() {
    sol::object comp = lua["CompCollision"];
    if (comp.is<sol::table>()) {
        sol::table comp_table = comp;
        b2BodyDef body_def;
        body_def.type = comp_table["body_type"];
        body_def.fixedRotation = comp_table["fix_angle"];

        Manager()->AddComponent<component::Collision>(OwnerID(), body_def);
        sol::table fixture_table = comp_table["fixtures"];
        for (const auto &pair : fixture_table) {
            sol::table fixture = pair.second;
            std::string shape = fixture["shape"];
            if (shape == "Polygon") {
                PopulatePolygonFixture(fixture);
            } else if (shape == "Circle") {
                PopulateCircleFixture(fixture);
            }
        }
    }
}

void LuaScript::InitSkin() {
    sol::object comp = lua["CompAnimation"];
    if (comp.is<sol::table>()) {
        Manager()->AddComponent<component::Skin>(OwnerID());
    }
}

void LuaScript::PopulatePolygonFixture(sol::table &table) {
    auto collision = Manager()->GetComponent<component::Collision>(OwnerID());
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

void LuaScript::PopulateCircleFixture(sol::table &table) {
    auto collision = Manager()->GetComponent<component::Collision>(OwnerID());
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

}  // namespace component
}  // namespace foggy
