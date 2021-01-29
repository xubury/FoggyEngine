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

void Resource::loadTexture(int id, const std::string &filename) {
    textures.load(id, filename);
}

void Resource::loadFont(int id, const std::string &filename) {
    fonts.load(id, filename);
}

}  // namespace foggy
