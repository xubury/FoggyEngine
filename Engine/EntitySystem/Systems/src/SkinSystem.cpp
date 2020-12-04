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
    CheckLua(luaL_dofile(L, filename.c_str()));

    lua_getglobal(L, "AnimSystem");
    if (lua_istable(L, -1)) {
        std::cout << "adding Animation system" << std::endl;
        manager->Add<foggy::es::SkinSystem>();
    }
    lua_pop(L, 1);
}

void LuaAnimation::InitComponent(es::EntityManager<es::DefaultEntity> *manager,
                                 int id, const std::string &filename) {
    CheckLua(luaL_dofile(L, filename.c_str()));
    manager->AddComponent<component::Skin>(id);
}

}  // namespace es
}  // namespace foggy
