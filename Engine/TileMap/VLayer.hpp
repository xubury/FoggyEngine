#ifndef VLAYER_H
#define VLAYER_H

#include <SFML/Graphics.hpp>
#include <list>

#include "TileMap/VMap.hpp"
namespace foggy {

class VLayer {
   public:
    VLayer(const VLayer&) = delete;
    VLayer& operator=(const VLayer&) = delete;

    VLayer(const std::string& type, int z = 0, bool is_static = false);
    virtual ~VLayer() = default;
    virtual void Sort() = 0;

    int Z() const;
    const std::string& GetType() const;

    bool IsStatic() const;

   protected:
    const bool m_is_static;
    sf::RenderTexture m_render_texture;
    sf::Sprite m_sprite;
    sf::FloatRect m_last_viewport;
    const std::string m_type;

   private:
    friend class VMap;
    virtual void Draw(sf::RenderTarget& target, sf::RenderStates states,
                      const sf::FloatRect& viewport) = 0;
    const int m_z;
};

}  // namespace foggy

#endif /* VLAYER_H */
