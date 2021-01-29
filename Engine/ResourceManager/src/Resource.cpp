#include "ResourceManager/Resource.hpp"

namespace foggy {

ResourceManager<sf::Texture, int> Resource::textures;

ResourceManager<sf::Font, int> Resource::fonts;

sol::state Resource::lua;

Resource::__Initializer Resource::__initializer__;

void Resource::init() {
    lua.open_libraries();
    lua.set_function("C_loadFont", loadFont);
    lua.set_function("C_loadTexture", loadTexture);
    runSrcipt("res/scripts/Resources.lua");
    lua["loadResources"]();
}

void Resource::runSrcipt(const std::string &filename) {
    auto res = lua.safe_script_file(filename);
    if (!res.valid()) {
        sol::error err = res;
        std::cout << err.what() << std::endl;
        return;
    }
}

int Resource::getResourceID(const std::string &table_name,
                            const std::string &name) {
    sol::table table = lua[table_name];
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
