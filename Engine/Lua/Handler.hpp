#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>

#include "EntitySystem/Components/Collision.hpp"
#include "EntitySystem/ES.hpp"
#include "EntitySystem/Systems/System.hpp"
#include "Lua/lunar.hpp"

/* Code Snippet(How to iterate over tabel):
 * lua_pushnil(L);
 * for (; lua_next(L, -2) != 0; lua_pop(L, 1)) {
 * if (!lua_istable(L, -1)) continue;
 * do something..
 * } */
namespace foggy {

class LuaHandler {
   public:
    LuaHandler(const LuaHandler &) = delete;
    LuaHandler &operator=(const LuaHandler &) = delete;
    static LuaHandler &Instance() {
        static LuaHandler h;
        return h;
    }
    void CheckLua(int r) {
        if (r != LUA_OK) {
            std::string errormsg = lua_tostring(L, -1);
            throw std::runtime_error(errormsg);
        }
    }
    lua_State *L;

    template <typename ENTITY>
    void InitSystem(es::SystemManager<ENTITY> *system) {
        CheckLua(luaL_dofile(L, "../Systems.lua"));
        lua_getglobal(L, "SkinSystem");
        if (lua_istable(L, -1)) {
            std::cout << "adding skin system" << std::endl;
            system->template Add<foggy::es::SkinSystem>();
        }
        lua_pop(L, 1);

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

            system->template Add<foggy::es::CollisionSystem>(x, y);
            m_world = system->template System<es::CollisionSystem>();
        }
        lua_pop(L, 1);
    }

    template <typename ENTITY>
    void InitComponent(es::EntityManager<ENTITY> *manager, int id,
                       const std::string &filename) {
        CheckLua(luaL_dofile(L, filename.c_str()));
        ProcessCompCollision(manager, id);
    }

   private:
    LuaHandler() {
        L = luaL_newstate();
        luaL_openlibs(L);
    }
    ~LuaHandler() { lua_close(L); }
    template <typename ENTITY>
    void ProcessCompCollision(es::EntityManager<ENTITY> *manager, int id) {
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

            auto collision =
                manager->template AddComponent<component::Collision>(
                    id, m_world, body_def);
            std::cout << "Comp Collision Added" << std::endl;

            // Adding Fixture
            lua_pushnil(L);
            for (; lua_next(L, -2) != 0; lua_pop(L, 1)) {
                if (!lua_istable(L, -1)) continue;
                std::cout << "Adding fixture"
                          << "\n";
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
                collision->AddFixture(fixture_def);
            }
            std::flush(std::cout);
        }
        lua_pop(L, 1);
    }

    es::CollisionSystem *m_world;
};
}  // namespace foggy

#endif /* HANDLER_H */
