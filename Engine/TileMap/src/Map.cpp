#include <fstream>
#include <iostream>

#include "TileMap/Layer.hpp"
#include "TileMap/Map.hpp"
#include "TileMap/Square.hpp"

namespace foggy {
VMap::VMap(float size) : m_tile_size(size) {}

bool VMap::loadFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        return loadFromStream(file);
    }
    return false;
}

bool VMap::loadFromStream(std::istream &in) {
    Json::Value root;
    Json::CharReaderBuilder rbuilder;
    std::string errs;
    bool succ = Json::parseFromStream(rbuilder, in, &root, &errs);
    if (!succ) {
        std::cout << "Failed to parse configuration\n" << errs;
        return false;
    } else {
        loadFromJson(root);
        return true;
    }
}

void VMap::add(VLayer *layer, bool sort) {
    m_layers.emplace_back(layer);

    if (sort) sortLayers();
}

void VMap::remove(VLayer *layer) {
    auto iter = std::find(m_layers.begin(), m_layers.end(), layer);
    if (iter != m_layers.end()) {
        m_layers.erase(iter);
    }
}

void VMap::remove(size_t index) {
    delete m_layers.at(index);
    m_layers.erase(m_layers.begin() + index);
}

std::size_t VMap::size() const { return m_layers.size(); }

VLayer *VMap::at(size_t index) const { return m_layers.at(index); }

void VMap::clear() {
    const std::size_t s = size();
    for (std::size_t i = 0; i < s; ++i) {
        delete (m_layers[i]);
    }
    m_layers.clear();
    m_textures.clear();
}

float VMap::getTileSize() const { return m_tile_size; }

sf::Vector2i VMap::mapCoordsToTile(const sf::Vector2f &pos) const {
    return mapCoordsToTile(pos.x, pos.y);
}

sf::Vector2f VMap::mapTileToCoords(const sf::Vector2i &pos) const {
    return mapTileToCoords(pos.x, pos.y);
}

void VMap::sortLayers() {
    std::sort(m_layers.begin(), m_layers.end(),
              [](const VLayer *lhs, const VLayer *rhs) {
                  return lhs->z() < rhs->z();
              });
    const std::size_t size = m_layers.size();
    for (std::size_t i = 0; i < size; ++i) {
        m_layers[i]->sort();
    }
}

void VMap::draw(sf::RenderTarget &target, sf::RenderStates states,
                const sf::FloatRect &viewport) const {
    sf::FloatRect delta_viewport(
        viewport.left - m_tile_size, viewport.top - m_tile_size,
        viewport.width + m_tile_size * 2, viewport.height + m_tile_size * 2);
    const std::size_t size = m_layers.size();
    for (std::size_t i = 0; i < size; ++i) {
        m_layers[i]->draw(target, states, delta_viewport);
    }
}

VMap *VMap::createMapFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        return createMapFromStream(file);
    }
    return nullptr;
}

VMap *VMap::createMapFromStream(std::istream &in) {
    Json::Value root;
    Json::CharReaderBuilder rbuilder;
    std::string errs;
    bool succ = Json::parseFromStream(rbuilder, in, &root, &errs);
    if (!succ) {
        std::cout << "Failed to parse configuration\n" << errs;
        return nullptr;
    } else {
        return createMapFromJson(root);
    }
}

VMap *VMap::createMapFromJson(Json::Value &root) {
    VMap *res = nullptr;

    Json::Value &geometry = root["geometry"];
    std::string geometry_name = geometry["name"].asString();
    float size = geometry["size"].asFloat();

    if (geometry_name == "Square") {
        res = new Map<geometry::Square>(size);
        res->loadFromJson(root);
    } else {
        std::cerr << "Unknow geometry '" << geometry_name << "'" << std::endl;
    }

    return res;
}

}  // namespace foggy
