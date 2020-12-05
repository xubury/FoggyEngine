#include <sol/sol.hpp>

#include "EntitySystem/Components/Skin.hpp"
#include "EntitySystem/Systems/SkinSystem.hpp"

namespace foggy {
namespace es {

void SkinSystem::Update(es::EntityManager<es::DefaultEntity> &manager,
                        const sf::Time &delta_time) {
    component::Skin::Handle skin;
    auto view = manager.GetByComponents<component::Skin>(skin);
    auto cur = view.Begin();
    auto end = view.End();
    for (; cur != end; ++cur) {
        skin->m_sprite.Update(delta_time);
    }
}

LuaAnimation::LuaAnimation(es::SystemManager<es::DefaultEntity> *manager,
                           const std::string &filename) {
    sol::state lua;
    lua.script_file(filename);
    sol::object system = lua["AnimSystem"];
    if (system.is<sol::table>()) {
        std::cout << "adding Animation system" << std::endl;
        manager->Add<foggy::es::SkinSystem>();
    }
}

void LuaAnimation::InitComponent(es::EntityManager<es::DefaultEntity> *manager,
                                 int id, const std::string &filename) {
    sol::state lua;
    lua.script_file(filename);
    manager->AddComponent<component::Skin>(id);
}

}  // namespace es
}  // namespace foggy
