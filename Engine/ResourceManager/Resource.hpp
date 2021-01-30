#ifndef RESOURCE_H
#define RESOURCE_H

#include <sol/sol.hpp>
#include <string>

#include "ResourceManager/ResourceManager.hpp"

namespace foggy {

class Resource {
   public:
    Resource(const Resource &) = delete;
    Resource &operator=(const Resource &) = delete;

    foggy::ResourceManager<sf::Texture, int> textures;

    foggy::ResourceManager<sf::Font, int> fonts;

    void runSrcipt(const std::string &filename);

    int getResourceID(const std::string &table, const std::string &name);

    static Resource &instance() {
        static Resource s;
        return s;
    }

    static sol::state &lua() { return instance().m_lua; }

   private:
    sol::state m_lua;

    Resource() { initLua(); }

    void initLua();
    void loadTexture(int id, const std::string &name);
    void loadFont(int id, const std::string &name);
    void loadAnimation(int id, int texture_id);
};

}  // namespace foggy

#endif /* RESOURCES_CONFIGURATION_H */
