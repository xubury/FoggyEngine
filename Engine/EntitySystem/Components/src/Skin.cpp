#include "EntitySystem/Components/Skin.hpp"

#include <utility>

namespace foggy {
namespace component {

Skin::Skin(sol::state &lua) : lua(lua) {
    lua.set_function("C_SetAnimation", [this](int id) {
        m_sprite.SetAnimation(m_animations[id]);
    });
    lua.set_function("C_SetLoop",
                     [this](bool loop) { m_sprite.SetLoop(loop); });
    lua.set_function("C_SetRepeat",
                     [this](int repeat) { m_sprite.SetRepeat(repeat); });
    lua.set_function("C_Play", [this]() { m_sprite.Play(); });
    lua.set_function("C_OnAnimFinish",
                     [this](std::function<void()> func) {
        //FIXME:How to pass lua callback properly??
         });
}

std::string Skin::GetCurrentState() { return lua["states"]["current"]; }

void Skin::Update() { lua["Update"](); }

}  // namespace component
}  // namespace foggy
