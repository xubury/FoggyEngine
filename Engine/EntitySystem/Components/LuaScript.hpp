#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <sol/sol.hpp>

#include "EntitySystem/ES.hpp"
namespace foggy {
namespace component {

struct LuaScript : es::Component<LuaScript, es::DefaultEntity> {
   public:
    explicit LuaScript() = default;
    void InitScript(const std::string &filename);
    sol::state lua;

   private:
    void InitComponent();
    void InitCollision();
    void InitSkin();
    void PopulatePolygonFixture(sol::table &table);

    void PopulateCircleFixture(sol::table &table);
};

}  // namespace component
}  // namespace foggy

#endif /* LUASCRIPT_H */
