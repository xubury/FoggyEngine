#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include <sol/sol.hpp>

#include "EntitySystem/ES.hpp"
namespace foggy {
namespace component {

struct LuaScript : es::Component<LuaScript, es::DefaultEntity> {
   public:
    LuaScript() = default;
    void initScript(const std::string &filename);
    sol::state lua;

   private:
    void initComponent();
    void initCollision();
    void initSkin();
    void populatePolygonFixture(sol::table &table);

    void populateCircleFixture(sol::table &table);
};

}  // namespace component
}  // namespace foggy

#endif /* LUASCRIPT_HPP */
