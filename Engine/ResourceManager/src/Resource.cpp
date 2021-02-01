#include "ResourceManager/Resource.hpp"

namespace foggy {

void Resource::initLua() {
    m_lua.open_libraries();
    m_lua.set_function("C_loadFont", [this](int id, const std::string &name) {
        this->loadFont(id, name);
    });
    m_lua.set_function("C_loadTexture",
                       [this](int id, const std::string &name) {
                           this->loadTexture(id, name);
                       });
    m_lua.set_function("C_loadCharacterAnimation",
                       [this](int id, int texture_id) {
                           this->loadCharacterAnimation(id, texture_id);
                       });
    runSrcipt("res/scripts/Resources.lua");
    runSrcipt("res/scripts/Animation.lua");
    m_lua["loadResources"]();
    m_lua["initAnimation"]();
}

void Resource::runSrcipt(const std::string &filename) {
    auto res = m_lua.safe_script_file(filename);
    if (!res.valid()) {
        sol::error err = res;
        std::cout << err.what() << std::endl;
        return;
    }
}

int Resource::getResourceID(const std::string &table_name,
                            const std::string &name) {
    sol::object table = m_lua[table_name];
    if (!table.valid()) {
        throw std::runtime_error("table name: " + table_name + " is invalid!");
    }
    sol::object id = table.as<sol::table>()[name];
    if (id.valid() && id.is<int>()) {
        return id.as<int>();
    } else {
        throw std::runtime_error("field name: " + name +
                                 " in table: " + table_name + " is invalid!");
        return -1;
    }
}

sol::table Resource::GetResouceTable(const std::string &table_name) {
    sol::object table = m_lua[table_name];
    if (!table.valid()) {
        throw std::runtime_error("table name: " + table_name + " is invalid!");
        return sol::table();
    }
    return table;
}

void Resource::loadTexture(int id, const std::string &filename) {
    textures.load(id, filename);
}

void Resource::loadFont(int id, const std::string &filename) {
    fonts.load(id, filename);
}

void Resource::loadCharacterAnimation(int id, int texture_id) {
    as::Animation &anim = character_anims.getOrLoad(id);
    anim.addFrame(&textures.get(texture_id));
}

}  // namespace foggy
