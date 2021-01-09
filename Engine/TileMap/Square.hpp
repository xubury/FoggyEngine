#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

namespace geometry {

struct Square {
    static const sf::ConvexShape& GetShape();
    static sf::Vector2f MapCoordsToPixel(int x, int y, float scale);
    static sf::Vector2i MapPixelToCoords(float x, float y, float scale);
    static sf::IntRect GetTextureRect(int x, int y, float scale);
    static sf::Vector2i Round(float x, float y);
    static int Distance(int x1, int y1, int x2, int y2);

   private:
    static sf::ConvexShape m_shape;
    static void Init();

    static struct __Initiatiser {
        __Initiatiser() { Square::Init(); };
    } __initiatiser__;
};

}  // namespace geometry

#endif /* SQUARE_H */
