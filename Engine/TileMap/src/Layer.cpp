#include "TileMap/Layer.hpp"

namespace foggy {

VLayer::VLayer(const std::string& type, int z, bool is_static)
    : m_is_static(is_static), m_type(type), m_z(z) {}

int VLayer::Z() const { return m_z; }

const std::string& VLayer::GetType() const { return m_type; }

bool VLayer::IsStatic() const { return m_is_static; }

}  // namespace foggy
