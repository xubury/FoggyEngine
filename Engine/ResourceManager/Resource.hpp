#ifndef RESOURCE_H
#define RESOURCE_H

#include <sol/sol.hpp>
#include <string>

#include "ResourceManager/ResourceManager.hpp"

namespace foggy {

class Resource {
   public:
    Resource() = delete;
    Resource(const Resource &) = delete;
    Resource &operator=(const Resource &) = delete;

    static foggy::ResourceManager<sf::Texture, int> textures;

    static foggy::ResourceManager<sf::Font, int> fonts;

    static sol::state lua;

    static void runSrcipt(const std::string &filename);

    static int getResourceID(const std::string &table, const std::string &name);

   private:
    static void init();
    static void loadTexture(int id, const std::string &name);
    static void loadFont(int id, const std::string &name);
    static void loadAnimation(int id, int texture_id);
    static struct __Initializer {
        __Initializer() { Resource::init(); };
    } __initializer__;
};

}  // namespace foggy

#endif /* RESOURCES_CONFIGURATION_H */
