#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

namespace foggy {

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

}  // namespace foggy

#endif /* TILE_H */
