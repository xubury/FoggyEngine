#include "EntitySystem/Components/Skin.hpp"

#include <utility>

#include "EntitySystem/Components/LuaScript.hpp"

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
    lua.set_function("C_setAnimation", [this](int id) {
        m_sprite.setAnimation(m_animations[id]);
    });
    lua.set_function("C_setLoop",
                     [this](bool loop) { m_sprite.setLoop(loop); });
    lua.set_function("C_setRepeat",
                     [this](int repeat) { m_sprite.setRepeat(repeat); });
    lua.set_function("C_play", [this]() { m_sprite.play(); });
    lua.set_function("C_isPlaying", [this]() {
        return m_sprite.getStatus() == as::AnimatedSprite::Playing;
    });
    lua.set_function("C_setSpriteScale",
                     [this](float x, float y) { m_sprite.setScale(x, y); });
    m_sprite.onFinished = [&lua]() { lua["CompAnimation"]["onFinished"](); };
}

}  // namespace component
}  // namespace foggy
