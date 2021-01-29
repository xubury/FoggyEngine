#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

namespace geometry {

struct Square {
    static const sf::ConvexShape& getShape();
    static sf::Vector2f mapTileToCoords(int x, int y, float scale);
    static sf::Vector2i mapCoordsToTile(float x, float y, float scale);
    static sf::IntRect getTextureRect(int x, int y, float scale);
    static sf::Vector2i round(float x, float y);
    static int distance(int x1, int y1, int x2, int y2);

   private:
    static sf::ConvexShape m_shape;
    static void init();

    static struct __Initializer {
        __Initializer() { Square::init(); };
    } __initializer__;
};

}  // namespace geometry

#endif /* SQUARE_H */
