#ifndef VMAP_H
#define VMAP_H

#include <json/json.h>
#include <json/value.h>

#include <SFML/Graphics.hpp>
#include <list>

#include "ResourceManager/ResourceManager.hpp"

namespace foggy {

class VLayer;

class VMap {
   public:
    VMap(const VMap&) = delete;
    VMap& operator=(const VMap&) = delete;

    VMap(float size);
    virtual ~VMap() = default;

    virtual void loadFromJson(const Json::Value& root) = 0;
    bool loadFromFile(const std::string& filename);
    bool loadFromStream(std::istream& in);

    void add(VLayer* layer, bool sort = true);
    void remove(VLayer* layer);
    void remove(std::size_t index);

    std::size_t size() const;
    VLayer* at(std::size_t index) const;
    void clear();

    float getTileSize() const;

    virtual sf::Vector2i mapPixelToCoords(float x, float y) const = 0;
    sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos) const;

    virtual sf::Vector2f mapCoordsToPixel(int x, int y) const = 0;
    sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos) const;

    virtual const sf::ConvexShape getShape() const = 0;

    virtual std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,
                                            const sf::Vector2i& dest) const = 0;
    virtual sf::Vector2i getPath1(const sf::Vector2i& origin,
                                  const sf::Vector2i& dest) const = 0;
    virtual int getDistance(const sf::Vector2i& origin,
                            const sf::Vector2i& dest) const = 0;

    static VMap* createMapFromFile(const std::string& filename);
    static VMap* createMapFromStream(std::istream& in);
    static VMap* createMapFromJson(Json::Value& root);

   protected:
    void sortLayers();
    const float m_tile_size;

    ResourceManager<sf::Texture, std::string> m_textures;

   private:
    friend class MapViewer;
    void draw(sf::RenderTarget& target, sf::RenderStates states,
              const sf::FloatRect& viewport) const;
    std::vector<VLayer*> m_layers;
};
}  // namespace foggy

#endif /* VMAP_H */
