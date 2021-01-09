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

    // convert pixel to word coord
    static sf::Vector2i MapPixelToCoords(float x, float y, float scale);
    static sf::Vector2i MapPixelToCoords(const sf::Vector2f& pos, float scale);

    // return the center of the tile position in pixel relative to the openGL
    // world
    static sf::Vector2f MapCoordsToPixel(int x, int y, float scale);
    static sf::Vector2f MapCoordsToPixel(const sf::Vector2i& pos, float scale);

    Tile(int pos_x, int pos_y, float scale);

    template <typename... Args>
    inline void SetFillColor(Args&&... args);

    template <typename... Args>
    void SetPosition(Args&&... args);

    sf::Vector2f GetPosition() const;

    template <typename... Args>
    void SetCoords(Args&&... args);

    void SetTexture(const sf::Texture* texture, bool resetRect = false);
    void SetTextureRect(const sf::IntRect& rect);

    sf::FloatRect GetGlobalBounds() const;
    sf::FloatRect GetLocalBounds() const;

   private:
    sf::ConvexShape m_shape;

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
};

template <typename GEOMETRY>
inline sf::Vector2i Tile<GEOMETRY>::MapPixelToCoords(float x, float y,
                                                     float scale) {
    return GEOMETRY::MapPixelToCoords(x, y, scale);
}

template <typename GEOMETRY>
inline sf::Vector2i Tile<GEOMETRY>::MapPixelToCoords(const sf::Vector2f& pos,
                                                     float scale) {
    return MapPixelToCoords(pos.x, pos.y, scale);
}

template <typename GEOMETRY>
inline sf::Vector2f Tile<GEOMETRY>::MapCoordsToPixel(int x, int y,
                                                     float scale) {
    return GEOMETRY::MapCoordsToPixel(x, y, scale);
}

template <typename GEOMETRY>
inline sf::Vector2f Tile<GEOMETRY>::MapCoordsToPixel(const sf::Vector2i& pos,
                                                     float scale) {
    return MapCoordsToPixel(pos.x, pos.y, scale);
}

template <typename GEOMETRY>
Tile<GEOMETRY>::Tile(int pos_x, int pos_y, float scale) {
    m_shape = GEOMETRY::GetShape();
    m_shape.setOutlineColor(sf::Color(255, 255, 255, 25));
    m_shape.setOutlineThickness(2.f / scale);
    m_shape.setScale(scale, scale);
    SetCoords(pos_x, pos_y);
}

template <typename GEOMETRY>
template <typename... Args>
inline void Tile<GEOMETRY>::SetFillColor(Args&&... args) {
    m_shape.setFillColor(std::forward<Args&>(args)...);
}

template <typename GEOMETRY>
template <typename... Args>
inline void Tile<GEOMETRY>::SetPosition(Args&&... args) {
    m_shape.setPosition(args...);
}

template <typename GEOMETRY>
template <typename... Args>
inline void Tile<GEOMETRY>::SetCoords(Args&&... args) {
    sf::Vector2f pos = mapCoordsToPixel(args..., m_shape.getScale().x);
    m_shape.setPosition(pos);
}

template <typename GEOMETRY>
inline sf::Vector2f Tile<GEOMETRY>::GetPosition() const {
    return m_shape.getPosition();
}

template <typename GEOMETRY>
inline void Tile<GEOMETRY>::SetTexture(const sf::Texture* texture,
                                       bool resetRect) {
    m_shape.setTexture(texture, resetRect);
}

template <typename GEOMETRY>
inline void Tile<GEOMETRY>::SetTextureRect(const sf::IntRect& rect) {
    m_shape.setTextureRect(rect);
}

template <typename GEOMETRY>
inline sf::FloatRect Tile<GEOMETRY>::GetGlobalBounds() const {
    return m_shape.getGlobalBounds();
}

template <typename GEOMETRY>
inline sf::FloatRect Tile<GEOMETRY>::GetLocalBounds() const {
    return m_shape.getLocalBounds();
}

template <typename GEOMETRY>
inline void Tile<GEOMETRY>::draw(sf::RenderTarget& target,
                                 sf::RenderStates states) const {
    target.draw(m_shape, states);
}
}  // namespace foggy

#endif /* TILE_H */
