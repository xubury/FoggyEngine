#include "EntitySystem/Components/Transform.hpp"
#define SOL_ALL_SAFETIES_ON 1
#include <box2d/box2d.h>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/Components/LuaScript.hpp"
#include "EntitySystem/Components/Skin.hpp"
#include "Utils/Converter.hpp"

namespace foggy {
namespace component {

void LuaScript::initScript(const std::string &filename) {
    lua.open_libraries();
    auto res = lua.safe_script_file(filename);
    if (!res.valid()) {
        sol::error err = res;
        std::cout << err.what() << std::endl;
        return;
    }
    lua.set_function("C_getSpeed", [this]() {
        b2Vec2 speed;
        if (manager()->hasComponent<foggy::component::Collision>(ownerID())) {
            foggy::component::Collision::Handle collision =
                manager()->getComponent<foggy::component::Collision>(ownerID());
            speed = collision->b2body_ref->GetLinearVelocity();
        }
        return std::make_tuple(speed.x, speed.y);
    });
    initComponent();
}

void LuaScript::initComponent() {
    initCollision();
    initSkin();
}

void LuaScript::initCollision() {
    sol::object comp = lua["CompCollision"];
    if (comp.is<sol::table>()) {
        sol::table comp_table = comp;
        b2BodyDef body_def;
        body_def.type = comp_table["body_type"];
        body_def.fixedRotation = comp_table["fix_angle"];
        body_def.linearDamping = comp_table["linear_damping"];

        manager()->addComponent<component::Collision>(ownerID(), body_def);
        sol::table fixture_table = comp_table["fixtures"];
        for (const auto &pair : fixture_table) {
            sol::table fixture = pair.second;
            std::string shape = fixture["shape"];
            if (shape == "Polygon") {
                populatePolygonFixture(fixture);
            } else if (shape == "Circle") {
                populateCircleFixture(fixture);
            }
        }
    }
}

void LuaScript::initSkin() {
    sol::object comp = lua["CompAnimation"];
    if (comp.is<sol::table>()) {
        auto skin = manager()->addComponent<component::Skin>(ownerID());
        skin->registerLuaScript();
    }
}

void LuaScript::populatePolygonFixture(sol::table &table) {
    auto collision = manager()->getComponent<component::Collision>(ownerID());
    auto trans = manager()->getComponent<component::Transform>(ownerID());
    sf::Vector2f scale = trans->getScale();
    sol::table vertices_table = table["vertices"];
    std::vector<b2Vec2> vertices;
    for (const auto &pair : vertices_table) {
        sol::table pos = pair.second;
        float x = pos["x"];
        float y = pos["y"];
        x *= scale.x;
        y *= scale.y;
        vertices.emplace_back(converter::pixelsToMeters(x),
                              converter::pixelsToMeters(y));
    }

    b2PolygonShape b2shape;
    b2shape.Set(vertices.data(), vertices.size());
    b2FixtureDef fixture_def;
    fixture_def.density = table["density"];
    fixture_def.density /= (scale.x * scale.y);
    fixture_def.friction = table["friction"];
    fixture_def.restitution = table["restitution"];
    fixture_def.shape = &b2shape;
    collision->addFixture(fixture_def);
}

void LuaScript::populateCircleFixture(sol::table &table) {
    auto collision = manager()->getComponent<component::Collision>(ownerID());
    b2CircleShape b2shape;
    float radius = table["radius"];
    b2shape.m_radius = converter::pixelsToMeters(radius);
    b2FixtureDef fixture_def;
    fixture_def.density = table["density"];
    fixture_def.friction = table["friction"];
    fixture_def.restitution = table["restitution"];
    fixture_def.shape = &b2shape;
    collision->addFixture(fixture_def);
}

}  // namespace component
}  // namespace foggy
