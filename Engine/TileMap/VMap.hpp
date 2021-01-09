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

    virtual void LoadFromJson(const Json::Value& root) = 0;
    bool LoadFromFile(const std::string& filename);
    bool LoadFromStream(std::istream& in);

    void Add(VLayer* layer, bool sort = true);
    void Remove(VLayer* layer);
    void Remove(std::size_t index);

    std::size_t Size() const;
    VLayer* At(std::size_t index) const;
    void Clear();

    float GetTileSize() const;

    virtual sf::Vector2i MapPixelToCoords(float x, float y) const = 0;
    sf::Vector2i MapPixelToCoords(const sf::Vector2f& pos) const;

    virtual sf::Vector2f MapCoordsToPixel(int x, int y) const = 0;
    sf::Vector2f MapCoordsToPixel(const sf::Vector2i& pos) const;

    virtual const sf::ConvexShape GetShape() const = 0;

    virtual std::list<sf::Vector2i> GetPath(const sf::Vector2i& origin,
                                            const sf::Vector2i& dest) const = 0;
    virtual sf::Vector2i GetPath1(const sf::Vector2i& origin,
                                  const sf::Vector2i& dest) const = 0;
    virtual int GetDistance(const sf::Vector2i& origin,
                            const sf::Vector2i& dest) const = 0;

    static VMap* CreateMapFromFile(const std::string& filename);
    static VMap* CreateMapFromStream(std::istream& in);
    static VMap* CreateMapFromJson(Json::Value& root);

   protected:
    void SortLayers();
    const float m_tile_size;

    ResourceManager<sf::Texture, std::string> m_textures;

   private:
    friend class MapViewer;
    void Draw(sf::RenderTarget& target, sf::RenderStates states,
              const sf::FloatRect& viewport) const;
    std::vector<VLayer*> m_layers;
};
}  // namespace foggy

#endif /* VMAP_H */
