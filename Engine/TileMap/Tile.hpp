#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

namespace foggy {

template <typename GEOMETRY>
class Tile : public sf::Drawable {
   public:
    Tile(const Tile&) = delete;
    Tile& operator=(const Tile&) = delete;

    Tile(Tile&&) = default;
    Tile& operator=(Tile&&) = default;

    // convert pixel to world coord
    static sf::Vector2i mapCoordsToTile(float x, float y, float scale);
    static sf::Vector2i mapCoordsToTile(const sf::Vector2f& pos, float scale);

    // return the center of the tile position in pixel relative to the openGL
    // world
    static sf::Vector2f mapTileToCoords(int x, int y, float scale);
    static sf::Vector2f mapTileToCoords(const sf::Vector2i& pos, float scale);

    Tile(int pos_x, int pos_y, float scale);

    template <typename... Args>
    inline void setFillColor(Args&&... args);

    template <typename... Args>
    void setPosition(Args&&... args);

    sf::Vector2f getPosition() const;

    template <typename... Args>
    void setCoords(Args&&... args);

    void setTexture(const sf::Texture* texture, bool resetRect = false);
    void setTextureRect(const sf::IntRect& rect);

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

   private:
    sf::ConvexShape m_shape;

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
};

template <typename GEOMETRY>
inline sf::Vector2i Tile<GEOMETRY>::mapCoordsToTile(float x, float y,
                                                    float scale) {
    return GEOMETRY::MapCoordsToTile(x, y, scale);
}

template <typename GEOMETRY>
inline sf::Vector2i Tile<GEOMETRY>::mapCoordsToTile(const sf::Vector2f& pos,
                                                    float scale) {
    return mapCoordsToTile(pos.x, pos.y, scale);
}

template <typename GEOMETRY>
inline sf::Vector2f Tile<GEOMETRY>::mapTileToCoords(int x, int y, float scale) {
    return GEOMETRY::mapTileToCoords(x, y, scale);
}

template <typename GEOMETRY>
inline sf::Vector2f Tile<GEOMETRY>::mapTileToCoords(const sf::Vector2i& pos,
                                                    float scale) {
    return mapTileToCoords(pos.x, pos.y, scale);
}

template <typename GEOMETRY>
Tile<GEOMETRY>::Tile(int pos_x, int pos_y, float scale) {
    m_shape = GEOMETRY::getShape();
    m_shape.setOutlineColor(sf::Color(255, 255, 255, 25));
    m_shape.setOutlineThickness(2.f / scale);
    m_shape.setScale(scale, scale);
    setCoords(pos_x, pos_y);
}

template <typename GEOMETRY>
template <typename... Args>
inline void Tile<GEOMETRY>::setFillColor(Args&&... args) {
    m_shape.setFillColor(std::forward<Args&>(args)...);
}

template <typename GEOMETRY>
template <typename... Args>
inline void Tile<GEOMETRY>::setPosition(Args&&... args) {
    m_shape.setPosition(args...);
}

template <typename GEOMETRY>
template <typename... Args>
inline void Tile<GEOMETRY>::setCoords(Args&&... args) {
    sf::Vector2f pos = mapTileToCoords(args..., m_shape.getScale().x);
    m_shape.setPosition(pos);
}

template <typename GEOMETRY>
inline sf::Vector2f Tile<GEOMETRY>::getPosition() const {
    return m_shape.getPosition();
}

template <typename GEOMETRY>
inline void Tile<GEOMETRY>::setTexture(const sf::Texture* texture,
                                       bool resetRect) {
    m_shape.setTexture(texture, resetRect);
}

template <typename GEOMETRY>
inline void Tile<GEOMETRY>::setTextureRect(const sf::IntRect& rect) {
    m_shape.setTextureRect(rect);
}

template <typename GEOMETRY>
inline sf::FloatRect Tile<GEOMETRY>::getGlobalBounds() const {
    return m_shape.getGlobalBounds();
}

template <typename GEOMETRY>
inline sf::FloatRect Tile<GEOMETRY>::getLocalBounds() const {
    return m_shape.getLocalBounds();
}

template <typename GEOMETRY>
inline void Tile<GEOMETRY>::draw(sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(m_shape, states);
}

}  // namespace foggy

#endif /* TILE_H */
