#include <utility>

#include "EntitySystem/Components/LuaScript.hpp"
#include "EntitySystem/Components/Skin.hpp"

namespace foggy {
namespace component {

Skin::Skin() {}

void Skin::Update() {
    auto lua_comp = Manager()->GetComponent<LuaScript>(OwnerID());
    sol::state &lua = lua_comp->lua;
    lua["Update"]();
}

void Skin::RegisterLuaScript() {
    auto lua_comp = Manager()->GetComponent<LuaScript>(OwnerID());
    sol::state &lua = lua_comp->lua;
    lua.set_function("C_SetAnimation", [this](int id) {
        m_sprite.SetAnimation(m_animations[id]);
    });
    lua.set_function("C_SetLoop",
                     [this](bool loop) { m_sprite.SetLoop(loop); });
    lua.set_function("C_SetRepeat",
                     [this](int repeat) { m_sprite.SetRepeat(repeat); });
    lua.set_function("C_Play", [this]() { m_sprite.Play(); });
    lua.set_function("C_IsPlaying", [this]() {
        return m_sprite.GetStatus() == as::AnimatedSprite::Playing;
    });
    lua.set_function("C_SetSpriteScale",
                     [this](float x, float y) { m_sprite.setScale(x, y); });
    m_sprite.OnFinished = [&lua]() { lua["CompAnimation"]["OnFinish"](); };
}

}  // namespace component
}  // namespace foggy
