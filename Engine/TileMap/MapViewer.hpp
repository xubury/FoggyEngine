#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <SFML/Graphics.hpp>

#include "ActionSystem/ActionTarget.hpp"

namespace foggy {

class VMap;
class MapViewer : public sf::Drawable, protected ActionTarget<int> {
   public:
    MapViewer(const MapViewer&) = delete;
    MapViewer& operator=(const MapViewer&) = delete;

    MapViewer(sf::RenderWindow& window, const VMap& map,
              const ActionMap<int>& action_map);

    using ActionTarget::bind;
    using ActionTarget::processEvent;
    using ActionTarget::processEvents;
    using ActionTarget::unbind;

    void move(float offset_x, float offset_y);
    void move(const sf::Vector2f& offset);

    void setPosition(float pos_x, float pos_y);
    void setPosition(const sf::Vector2f& pos);

    sf::Vector2f getPosition() const;

    void zoom(float factor);
    float getZoom() const;

    void setSize(float width, float height);
    void setSize(const sf::Vector2f& size);

    void update(const sf::Time& deltaTime);

    void setSpeed(float speed);

    void draw(sf::RenderStates states = sf::RenderStates::Default) const;

    sf::Vector2f mapScreenToCoords(int x, int y) const;
    sf::Vector2f mapScreenToCoords(const sf::Vector2i& pos) const;

    sf::Vector2i mapCoordsToScreen(float x, float y) const;
    sf::Vector2i mapCoordsToScreen(const sf::Vector2f& pos) const;

    sf::Vector2f mapPixelToCoords(float x, float y) const;
    sf::Vector2f mapPixelToCoords(const sf::Vector2f& pos) const;

    sf::Vector2f mapCoordsToPixel(float x, float y) const;
    sf::Vector2f mapCoordsToPixel(const sf::Vector2f& pos) const;

   private:
    const VMap& m_map;
    sf::View m_view;
    int m_move_x;
    int m_move_y;
    float m_movement_speed;
    float m_zoom;
    sf::RenderWindow& m_window;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}  // namespace foggy

#endif /* MAPVIEWER_H */
