#ifndef LUA_UTILS_HPP
#define LUA_UTILS_HPP

#include <lua.hpp>
#include <stdexcept>
#include <string>

#define LUA_BEGIN_ENUM_TABLE(L) lua_newtable(L);
#define LUA_ENUM_REGISTER(L, Name) \
    lua_pushliteral(L, #Name);     \
    lua_pushnumber(L, Name);       \
    lua_settable(L, -3);
#define LUA_END_ENUM_TABLE(L, NameSpace) lua_setglobal(L, #NameSpace);

namespace foggy {
inline void CheckLua(lua_State *L, int r) {
    if (r != LUA_OK) {
        std::string errormsg = lua_tostring(L, -1);
        throw std::runtime_error(errormsg);
    }
}
}  // namespace foggy

#endif
