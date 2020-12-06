#include "EntitySystem/Components/Skin.hpp"

namespace foggy {
namespace component {

Skin::Skin(sol::state &lua) : lua(lua) {
    lua.set_function("C_SetAnimation", [this](int id) {
        m_sprite.SetAnimation(m_animations[id]);
    });
    lua.set_function("C_Play", [this]() { m_sprite.Play(); });
}

std::string Skin::GetCurrentState() { return lua["states"]["current"]; }

void Skin::Update() { lua["Update"](); }

}  // namespace component
}  // namespace foggy
