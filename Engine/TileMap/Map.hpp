#ifndef MAP_H
#define MAP_H

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

template <typename GEOMETRY>
class Map : public VMap {
   public:
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    Map(float size);

    void LoadFromJson(const Json::Value& root) override;

    virtual sf::Vector2i MapPixelToCoords(float x, float y) const override;

    virtual sf::Vector2f MapCoordsToPixel(int x, int y) const override;

    virtual const sf::ConvexShape GetShape() const override;

    virtual std::list<sf::Vector2i> GetPath(
        const sf::Vector2i& origin, const sf::Vector2i& dest) const override;
    virtual sf::Vector2i GetPath1(const sf::Vector2i& origin,
                                  const sf::Vector2i& dest) const override;
    virtual int GetDistance(const sf::Vector2i& origin,
                            const sf::Vector2i& dest) const override;
};

template <typename GEOMETRY>
Map<GEOMETRY>::Map(float size) : VMap(size) {}

template <typename GEOMETRY>
void Map<GEOMETRY>::LoadFromJson(const Json::Value& root) {
    auto iter = root["layers"].begin();
    auto end = root["layers"].begin();
    for (; iter != end; ++iter) {
        const Json::Value& layer = *iter;
        std::string content = layer["content"].asString();
        // int z = 0;
        // try {
        //     z = layer["z"].asInt();
        // } catch (...) {
        // }

        // bool isStatic = false;
        // try {
        //     isStatic = layer["static"].asBool();
        // } catch (...) {
        // }
    }
    SortLayers();
}

template <typename GEOMETRY>
sf::Vector2i Map<GEOMETRY>::MapPixelToCoords(float x, float y) const {
    return GEOMETRY::MapPixelToCoords(x, y, m_tile_size);
}

template <typename GEOMETRY>
sf::Vector2f Map<GEOMETRY>::MapCoordsToPixel(int x, int y) const {
    return GEOMETRY::MapCoordsToPixel(x, y, m_tile_size);
}

template <typename GEOMETRY>
const sf::ConvexShape Map<GEOMETRY>::GetShape() const {
    sf::ConvexShape shape = GEOMETRY::GetShape();
    shape.setScale(m_tile_size, m_tile_size);
    return shape;
}

template <typename GEOMETRY>
std::list<sf::Vector2i> Map<GEOMETRY>::GetPath(const sf::Vector2i& origin,
                                               const sf::Vector2i& dest) const {
    int distance = GEOMETRY::Distance(origin.x, origin.y, dest.x, dest.y);
    std::list<sf::Vector2i> res;
    sf::Vector2f p(dest.x - origin.x, dest.y - origin.y);
    float delta = 1.0 / distance;
    float cumul = 0;
    res.emplace_back(origin);
    for (int i = 0; i < distance; ++i) {
        sf::Vector2i pos =
            GEOMETRY::Round(origin.x + p.x * cumul, origin.y + p.y * cumul);
        if (res.back() != pos) res.emplace_back(pos);
        cumul += delta;
    }
    if (res.back() != dest) res.emplace_back(dest);
    return res;
}

template <typename GEOMETRY>
sf::Vector2i Map<GEOMETRY>::GetPath1(const sf::Vector2i& origin,
                                     const sf::Vector2i& dest) const {
    int distance = GEOMETRY::Distance(origin.x, origin.y, dest.x, dest.y);
    sf::Vector2i res = origin;
    sf::Vector2f p(dest.x - origin.x, dest.y - origin.y);
    float delta = 1.0 / distance;
    float cumul = 0;
    for (int i = 0; i < distance; ++i) {
        sf::Vector2i pos =
            GEOMETRY::Round(origin.x + p.x * cumul, origin.y + p.y * cumul);
        if (pos != res) {
            res = pos;
            break;
        }
        cumul += delta;
    }
    return res;
}

template <typename GEOMETRY>
int Map<GEOMETRY>::GetDistance(const sf::Vector2i& origin,
                               const sf::Vector2i& dest) const {
    return GEOMETRY::Distance(origin.x, origin.y, dest.x, dest.y);
}

}  // namespace foggy

#endif /* MAP_H */
