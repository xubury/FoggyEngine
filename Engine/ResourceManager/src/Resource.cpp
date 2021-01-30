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
    runSrcipt("res/scripts/Resources.lua");
    m_lua["loadResources"]();
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
    sol::table table = lua()[table_name];
    if (!table.valid()) {
        std::cout << "table name:" << table_name << " is invalid!" << std::endl;
        return -1;
    }
    sol::object id = table[name];
    if (id.is<int>()) {
        return id.as<int>();
    } else {
        std::cout << "field name:" << name << " in table:" << table_name
                  << " is invalid!" << std::endl;
        return -1;
    }
}

void Resource::loadTexture(int id, const std::string &filename) {
    textures.load(id, filename);
}

void Resource::loadFont(int id, const std::string &filename) {
    fonts.load(id, filename);
}

}  // namespace foggy
