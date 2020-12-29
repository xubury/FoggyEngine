#include <fstream>
#include <iostream>

#include "TileMap/Layer.hpp"
#include "TileMap/Map.hpp"
#include "TileMap/Square.hpp"

namespace foggy {
VMap::VMap(float size) : m_tile_size(size) {}

bool VMap::LoadFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        return LoadFromStream(file);
    }
    return false;
}

bool VMap::LoadFromStream(std::istream &in) {
    Json::Value root;
    Json::CharReaderBuilder rbuilder;
    std::string errs;
    bool succ = Json::parseFromStream(rbuilder, in, &root, &errs);
    if (!succ) {
        std::cout << "Failed to parse configuration\n" << errs;
        return false;
    } else {
        LoadFromJson(root);
        return true;
    }
}

void VMap::Add(VLayer *layer, bool sort) {
    m_layers.emplace_back(layer);

    if (sort) SortLayers();
}

void VMap::Remove(VLayer *layer) {
    auto iter = std::find(m_layers.begin(), m_layers.end(), layer);
    if (iter != m_layers.end()) {
        m_layers.erase(iter);
    }
}

void VMap::Remove(size_t index) {
    delete m_layers.at(index);
    m_layers.erase(m_layers.begin() + index);
}

std::size_t VMap::Size() const { return m_layers.size(); }

VLayer *VMap::At(size_t index) const { return m_layers.at(index); }

void VMap::Clear() {
    const std::size_t size = Size();
    for (std::size_t i = 0; i < size; ++i) {
        delete (m_layers[i]);
    }
    m_layers.clear();
    m_textures.Clear();
}

float VMap::GetTileSize() const { return m_tile_size; }

sf::Vector2i VMap::MapPixelToCoords(const sf::Vector2f &pos) const {
    return MapPixelToCoords(pos.x, pos.y);
}

sf::Vector2f VMap::MapCoordsToPixel(const sf::Vector2i &pos) const {
    return MapCoordsToPixel(pos.x, pos.y);
}

void VMap::SortLayers() {
    std::sort(m_layers.begin(), m_layers.end(),
              [](const VLayer *lhs, const VLayer *rhs) {
                  return lhs->Z() < rhs->Z();
              });
    const std::size_t size = m_layers.size();
    for (std::size_t i = 0; i < size; ++i) {
        m_layers[i]->Sort();
    }
}

void VMap::Draw(sf::RenderTarget &target, sf::RenderStates states,
                const sf::FloatRect &viewport) const {
    sf::FloatRect delta_viewport(
        viewport.left - m_tile_size, viewport.top - m_tile_size,
        viewport.width + m_tile_size * 2, viewport.height + m_tile_size * 2);
    const std::size_t size = m_layers.size();
    for (std::size_t i = 0; i < size; ++i) {
        m_layers[i]->Draw(target, states, delta_viewport);
    }
}

VMap *VMap::CreateMapFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        return CreateMapFromStream(file);
    }
    return nullptr;
}

VMap *VMap::CreateMapFromStream(std::istream &in) {
    Json::Value root;
    Json::CharReaderBuilder rbuilder;
    std::string errs;
    bool succ = Json::parseFromStream(rbuilder, in, &root, &errs);
    if (!succ) {
        std::cout << "Failed to parse configuration\n" << errs;
        return nullptr;
    } else {
        return CreateMapFromJson(root);
    }
}

VMap *VMap::CreateMapFromJson(Json::Value &root) {
    VMap *res = nullptr;

    Json::Value &geometry = root["geometry"];
    std::string geometry_name = geometry["name"].asString();
    float size = geometry["size"].asFloat();

    if (geometry_name == "Square") {
        res = new Map<geometry::Square>(size);
        res->LoadFromJson(root);
    } else {
        std::cerr << "Unknow geometry '" << geometry_name << "'" << std::endl;
    }

    return res;
}

}  // namespace foggy
