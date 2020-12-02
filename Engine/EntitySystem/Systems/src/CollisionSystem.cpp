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

void LuaCollision::InitSystem(es::SystemManager<es::DefaultEntity> *manager) {
    CheckLua(luaL_dofile(L, "../Systems.lua"));

    lua_getglobal(L, "CollisionSystem");
    if (lua_istable(L, -1)) {
        std::cout << "adding collision system" << std::endl;
        lua_pushstring(L, "y");
        lua_gettable(L, -2);
        float y = lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "x");
        lua_gettable(L, -2);
        float x = lua_tonumber(L, -1);
        lua_pop(L, 1);

        manager->Add<foggy::es::CollisionSystem>(x, y);
        m_world = manager->System<es::CollisionSystem>();
    }
    lua_pop(L, 1);
}

void LuaCollision::InitComponent(es::EntityManager<es::DefaultEntity> *manager,
                                 int id, const std::string &filename) {
    assert(m_world != nullptr);
    CheckLua(luaL_dofile(L, filename.c_str()));
    ProcessCompCollision(manager, id);
}

void LuaCollision::ProcessCompCollision(
    es::EntityManager<es::DefaultEntity> *manager, int id) {
    lua_getglobal(L, "CompCollision");
    if (lua_istable(L, -1)) {
        lua_pushstring(L, "body_type");
        lua_gettable(L, -2);
        b2BodyType type = (b2BodyType)lua_tointeger(L, -1);
        lua_pop(L, 1);

        lua_pushstring(L, "fix_angle");
        lua_gettable(L, -2);
        bool fix_angle = lua_toboolean(L, -1);
        lua_pop(L, 1);

        b2BodyDef body_def;
        body_def.type = type;
        body_def.fixedRotation = fix_angle;

        component::Collision::Handle collision =
            manager->AddComponent<component::Collision>(id, m_world, body_def);
        std::cout << "Comp Collision Added" << std::endl;

        // Adding Fixture
        lua_pushnil(L);
        for (; lua_next(L, -2) != 0; lua_pop(L, 1)) {
            if (!lua_istable(L, -1)) continue;
            lua_pushstring(L, "shape");
            lua_gettable(L, -2);
            std::string shape = lua_tostring(L, -1);
            lua_pop(L, 1);
            if (shape == "Polygon") {
                std::cout << "Adding " << shape << " fixture"
                          << "\n";
                PopulatePolygonFixture(collision);
            }
        }
        std::flush(std::cout);
    }
    lua_pop(L, 1);
}

void LuaCollision::PopulatePolygonFixture(
    component::Collision::Handle &handle) {
    lua_pushstring(L, "width");
    lua_gettable(L, -2);
    float width = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "height");
    lua_gettable(L, -2);
    float height = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "density");
    lua_gettable(L, -2);
    float density = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "friction");
    lua_gettable(L, -2);
    float friction = lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "restitution");
    lua_gettable(L, -2);
    float restitution = lua_tonumber(L, -1);
    lua_pop(L, 1);

    b2PolygonShape b2shape;
    b2shape.SetAsBox(converter::PixelsToMeters(width / 2),
                     converter::PixelsToMeters(height / 2));
    b2FixtureDef fixture_def;
    fixture_def.density = density * (32 * 32);
    fixture_def.friction = friction;
    fixture_def.restitution = restitution;
    fixture_def.shape = &b2shape;
    handle->AddFixture(fixture_def);
}

}  // namespace es
}  // namespace foggy
