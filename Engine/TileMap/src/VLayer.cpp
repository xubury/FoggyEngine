#include "TileMap/Layer.hpp"

namespace foggy {

VLayer::VLayer(const std::string& type, int z, bool is_static)
    : m_is_static(is_static), m_type(type), m_z(z) {}

int VLayer::z() const { return m_z; }

const std::string& VLayer::getType() const { return m_type; }

bool VLayer::isStatic() const { return m_is_static; }

}  // namespace foggy
