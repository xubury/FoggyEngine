#include <utility>

#include "EntitySystem/Components/LuaScript.hpp"
#include "EntitySystem/Components/Skin.hpp"

namespace foggy {
namespace component {

Skin::Skin() {}

void Skin::update() {
    auto lua_comp = manager()->getComponent<LuaScript>(ownerID());
    sol::state &lua = lua_comp->lua;
    lua["update"]();
}

void Skin::registerLuaScript() {
    auto lua_comp = manager()->getComponent<LuaScript>(ownerID());
    sol::state &lua = lua_comp->lua;
    lua.set_function("C_SetAnimation", [this](int id) {
      m_sprite.setAnimation(m_animations[id]);
    });
    lua.set_function("C_SetLoop",
                     [this](bool loop) { m_sprite.setLoop(loop); });
    lua.set_function("C_SetRepeat",
                     [this](int repeat) { m_sprite.setRepeat(repeat); });
    lua.set_function("C_Play", [this]() { m_sprite.play(); });
    lua.set_function("C_IsPlaying", [this]() {
        return m_sprite.getStatus() == as::AnimatedSprite::Playing;
    });
    lua.set_function("C_SetSpriteScale",
                     [this](float x, float y) { m_sprite.setScale(x, y); });
    m_sprite.OnFinished = [&lua]() { lua["CompAnimation"]["OnFinish"](); };
}

}  // namespace component
}  // namespace foggy
