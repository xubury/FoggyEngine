#ifndef MAP_H
#define MAP_H

#include "TileMap/Layer.hpp"
#include "TileMap/Tile.hpp"
#include "TileMap/VMap.hpp"
#include "iostream"

namespace foggy {

template <typename GEOMETRY>
class Map : public VMap {
   public:
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    Map(float size);

    void loadFromJson(const Json::Value& root) override;

    virtual sf::Vector2f mapPixelToCoords(float x, float y) const override;

    virtual sf::Vector2f mapCoordsToPixel(float x, float y) const override;

    virtual const sf::ConvexShape getShape() const override;

    virtual std::list<sf::Vector2i> getPath(
        const sf::Vector2i& origin, const sf::Vector2i& dest) const override;
    virtual sf::Vector2i getPath1(const sf::Vector2i& origin,
                                  const sf::Vector2i& dest) const override;
    virtual int getDistance(const sf::Vector2i& origin,
                            const sf::Vector2i& dest) const override;
};

template <typename GEOMETRY>
Map<GEOMETRY>::Map(float size) : VMap(size) {}

template <typename GEOMETRY>
void Map<GEOMETRY>::loadFromJson(const Json::Value& root) {
    auto iter = root["layers"].begin();
    auto end = root["layers"].end();
    for (; iter != end; ++iter) {
        const Json::Value& layer = *iter;
        std::string content = layer["content"].asString();
        int z = 0;
        try {
            z = layer["z"].asInt();
        } catch (...) {
        }

        bool isStatic = false;
        try {
            isStatic = layer["static"].asBool();
        } catch (...) {
        }

        if (content == "tile") {
            auto current_layer =
                new Layer<Tile<GEOMETRY>>(content, z, isStatic);
            auto data_iter = layer["datas"].begin();
            auto data_end = layer["datas"].end();
            for (; data_iter != data_end; ++data_iter) {
                const Json::Value& texture = *data_iter;
                int tex_x = texture["x"].asInt();
                int tex_y = texture["y"].asInt();
                int height = std::max<int>(0, texture["height"].asInt());
                int width = std::max<int>(0, texture["width"].asInt());
                std::string img = texture["img"].asString();
                sf::Texture& tex = m_textures.getOrLoad(img, img);
                tex.setRepeated(true);
                for (int y = tex_y; y < tex_y + height; ++y) {
                    for (int x = tex_x; x < tex_x + width; ++x) {
                        Tile<GEOMETRY> tile(x, y, getTileSize());
                        tile.setTexture(&tex);
                        tile.setTextureRect(
                            GEOMETRY::getTextureRect(x, y, getTileSize()));
                        current_layer->add(std::move(tile), false);
                    }
                }
                add(current_layer, false);
            }
        } else if (content == "sprite") {
            auto current_layer = new Layer<sf::Sprite>(content, z, isStatic);
            auto data_iter = layer["datas"].begin();
            auto data_end = layer["datas"].end();
            for (; data_iter != data_end; ++data_iter) {
                const Json::Value& data = *data_iter;
                int x = data["x"].asInt();
                int y = data["y"].asInt();
                float ox = 0.5;
                float oy = 1;
                try {
                    ox = data["ox"].asFloat();
                } catch (...) {
                }

                try {
                    oy = data["oy"].asFloat();
                } catch (...) {
                }

                std::string img = data["img"].asString();

                sf::Sprite spr(m_textures.getOrLoad(img, img));
                spr.setPosition(GEOMETRY::mapCoordsToPixel(x, y, m_tile_size));

                sf::FloatRect rec = spr.getLocalBounds();
                spr.setOrigin(rec.width * ox, rec.height * oy);

                current_layer->add(std::move(spr), false);
            }
            add(current_layer, false);
        }
    }
    sortLayers();
}

template <typename GEOMETRY>
sf::Vector2f Map<GEOMETRY>::mapPixelToCoords(float x, float y) const {
    return GEOMETRY::mapPixelToCoords(x, y, m_tile_size);
}

template <typename GEOMETRY>
sf::Vector2f Map<GEOMETRY>::mapCoordsToPixel(float x, float y) const {
    return GEOMETRY::mapCoordsToPixel(x, y, m_tile_size);
}

template <typename GEOMETRY>
const sf::ConvexShape Map<GEOMETRY>::getShape() const {
    sf::ConvexShape shape = GEOMETRY::getShape();
    shape.setScale(m_tile_size, m_tile_size);
    return shape;
}

template <typename GEOMETRY>
std::list<sf::Vector2i> Map<GEOMETRY>::getPath(const sf::Vector2i& origin,
                                               const sf::Vector2i& dest) const {
    int distance = GEOMETRY::distance(origin.x, origin.y, dest.x, dest.y);
    std::list<sf::Vector2i> res;
    sf::Vector2f p(dest.x - origin.x, dest.y - origin.y);
    float delta = 1.0 / distance;
    float cumul = 0;
    res.emplace_back(origin);
    for (int i = 0; i < distance; ++i) {
        sf::Vector2i pos =
            GEOMETRY::round(origin.x + p.x * cumul, origin.y + p.y * cumul);
        if (res.back() != pos) res.emplace_back(pos);
        cumul += delta;
    }
    if (res.back() != dest) res.emplace_back(dest);
    return res;
}

template <typename GEOMETRY>
sf::Vector2i Map<GEOMETRY>::getPath1(const sf::Vector2i& origin,
                                     const sf::Vector2i& dest) const {
    int distance = GEOMETRY::distance(origin.x, origin.y, dest.x, dest.y);
    sf::Vector2i res = origin;
    sf::Vector2f p(dest.x - origin.x, dest.y - origin.y);
    float delta = 1.0 / distance;
    float cumul = 0;
    for (int i = 0; i < distance; ++i) {
        sf::Vector2i pos =
            GEOMETRY::round(origin.x + p.x * cumul, origin.y + p.y * cumul);
        if (pos != res) {
            res = pos;
            break;
        }
        cumul += delta;
    }
    return res;
}

template <typename GEOMETRY>
int Map<GEOMETRY>::getDistance(const sf::Vector2i& origin,
                               const sf::Vector2i& dest) const {
    return GEOMETRY::distance(origin.x, origin.y, dest.x, dest.y);
}

}  // namespace foggy

#endif /* MAP_H */
