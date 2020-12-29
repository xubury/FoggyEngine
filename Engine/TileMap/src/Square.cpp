#include <cmath>

#include "TileMap/Square.hpp"
namespace geometry {

sf::ConvexShape Square::m_shape;
Square::__Initiatiser Square::__initiatiser__;

const float height = 2;

const sf::ConvexShape& Square::GetShape() { return m_shape; }

sf::Vector2f Square::MapCoordsToPixel(int X, int Y, float scale) {
    return sf::Vector2f(X * scale * height, Y * scale * height);
}

sf::Vector2i Square::MapPixelToCoords(float X, float Y, float scale) {
    return Round(X / scale / height, Y / scale / height);
}

sf::Vector2i Square::Round(float x, float y) {
    return sf::Vector2i(x + 0.5, y + 0.5);
}

sf::IntRect Square::GetTextureRect(int x, int y, float scale) {
    sf::Vector2f pos = MapCoordsToPixel(x, y, scale);
    sf::IntRect res(pos.x, pos.y, height * scale, height * scale);
    return res;
}

int Square::Distance(int x1, int y1, int x2, int y2) {
    float x = x1 - x2;
    x = x * x;

    float y = y1 - y2;
    y = y * y;

    return ceil(sqrt(x + y));
}

void Square::Init() {
    m_shape.setPointCount(4);
    m_shape.setPoint(0, sf::Vector2f(0, 0));
    m_shape.setPoint(1, sf::Vector2f(0, height));
    m_shape.setPoint(2, sf::Vector2f(height, height));
    m_shape.setPoint(3, sf::Vector2f(height, 0));

    m_shape.setOrigin(height / 2, height / 2);
}

}  // namespace geometry
