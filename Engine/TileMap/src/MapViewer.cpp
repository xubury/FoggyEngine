#include "TileMap/MapViewer.hpp"
#include "TileMap/VMap.hpp"

namespace foggy {

MapViewer::MapViewer(sf::RenderWindow& window, const VMap& map,
                     const ActionMap<int>& action_map)
    : ActionTarget<int>(action_map), m_map(map), m_window(window) {
    // bind(Action(sf::Event::MouseWheelMoved), [this](const sf::Event& event) {
    //     zoom(1 - (event.mouseWheel.delta / 5.0f));
    // });
    auto size = m_window.getSize();
    setSize(size.x, size.y);
}

void MapViewer::move(float offset_x, float offset_y) {
    m_view.move(offset_x, offset_y);
}

void MapViewer::move(const sf::Vector2f& offset) { move(offset.x, offset.y); }

void MapViewer::setPosition(float pos_x, float pos_y) {
    m_view.setCenter(pos_x, pos_y);
}

void MapViewer::setPosition(const sf::Vector2f& pos) {
    setPosition(pos.x, pos.y);
}

sf::Vector2f MapViewer::getPosition() const { return m_view.getCenter(); }

void MapViewer::zoom(float factor) {
    m_zoom *= factor;
    m_view.zoom(factor);
}

float MapViewer::getZoom() const { return m_zoom; }

void MapViewer::setSize(float width, float height) {
    m_view.setSize(width, height);
}

void MapViewer::setSize(const sf::Vector2f& size) { setSize(size.x, size.y); }

void MapViewer::update(const sf::Time& delta_time) {
    if (m_move_x || m_move_y) {
        float delta =
            m_map.getTileSize() * m_movement_speed * delta_time.asSeconds();
        move(m_move_x * delta, m_move_y * delta);
    }
    m_move_x = 0;
    m_move_y = 0;
}

void MapViewer::setSpeed(float speed) { m_movement_speed = speed; }

void MapViewer::draw(sf::RenderStates states) const { draw(m_window, states); }

sf::Vector2i MapViewer::mapPixelToTile(int x, int y) const {
    sf::Vector2f pos = mapPixelToCoords(x, y);
    return m_map.mapCoordsToTile(pos.x, pos.y);
}

sf::Vector2i MapViewer::mapPixelToTile(const sf::Vector2i& pos) const {
    return mapPixelToTile(pos.x, pos.y);
}

sf::Vector2i MapViewer::mapTileToPixel(int x, int y) const {
    sf::Vector2f pos = m_map.mapTileToCoords(x, y);
    return m_window.mapCoordsToPixel(pos, m_view);
}

sf::Vector2i MapViewer::mapTileToPixel(const sf::Vector2i& pos) const {
    return mapTileToPixel(pos.x, pos.y);
}

sf::Vector2f MapViewer::mapPixelToCoords(int x, int y) const {
    return m_window.mapPixelToCoords(sf::Vector2i(x, y), m_view);
}

sf::Vector2f MapViewer::mapPixelToCoords(const sf::Vector2i& pos) const {
    return m_window.mapPixelToCoords(pos, m_view);
}

sf::Vector2i MapViewer::mapCoordsToPixel(float x, float y) const {
    return m_window.mapCoordsToPixel(sf::Vector2f(x, y), m_view);
}

sf::Vector2i MapViewer::mapCoordsToPixel(const sf::Vector2f& pos) const {
    return m_window.mapCoordsToPixel(pos, m_view);
}

sf::Vector2i MapViewer::mapCoordsToTile(float x, float y) const {
    return m_map.mapCoordsToTile(x, y);
}

sf::Vector2i MapViewer::mapCoordsToTile(const sf::Vector2f& pos) const {
    return mapCoordsToTile(pos.x, pos.y);
}

sf::Vector2f MapViewer::mapTileToCoords(int x, int y) const {
    return m_map.mapTileToCoords(x, y);
}

sf::Vector2f MapViewer::mapTileToCoords(const sf::Vector2i& pos) const {
    return mapTileToCoords(pos.x, pos.y);
}

void MapViewer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::View view = target.getView();
    target.setView(m_view);
    m_map.draw(
        target, states,
        sf::FloatRect(target.mapPixelToCoords(sf::Vector2i(0, 0), m_view),
                      m_view.getSize()));
    target.setView(view);
}

}  // namespace foggy
