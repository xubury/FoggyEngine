#ifndef LAYER_H
#define LAYER_H

#include "TileMap/VLayer.hpp"
#include "TileMap/VMap.hpp"

namespace foggy {

template <typename CONTENT>
class Layer : public VLayer {
   public:
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    Layer(const std::string& type, int z = 0, bool is_static = false);

    CONTENT* add(const CONTENT& content, bool resort = true);
    CONTENT* add(CONTENT&& content, bool resort = true);

    std::list<CONTENT*> getByCoords(const sf::Vector2i& coords,
                                    const VMap& map);

    bool remove(const CONTENT* content_ptr, bool resort = true);

    virtual void sort() override;

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states,
                      const sf::FloatRect& viewport) override;

    std::list<CONTENT> m_content;
};

template <typename CONTENT>
class Layer<CONTENT*> : public VLayer {
   public:
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    Layer(const std::string& type, int z = 0, bool is_static = false);

    CONTENT* Add(CONTENT* content, bool resort = true);

    std::list<CONTENT*> getByCoords(const sf::Vector2i& coords,
                                    const VMap& map);

    bool remove(const CONTENT* content_ptr, bool resort = true);

    virtual void sort() override;

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states,
                      const sf::FloatRect& viewport) override;

    std::list<CONTENT*> m_content;
};

template <typename CONTENT>
Layer<CONTENT>::Layer(const std::string& type, int z, bool is_static)
    : VLayer(type, z, is_static) {}

template <typename CONTENT>
CONTENT* Layer<CONTENT>::add(const CONTENT& content, bool resort) {
    m_content.emplace_back(content);
    CONTENT* res = m_content.back();
    if (resort) sort();

    return res;
}

template <typename CONTENT>
CONTENT* Layer<CONTENT>::add(CONTENT&& content, bool resort) {
    m_content.emplace_back(std::move(content));
    CONTENT* res = &m_content.back();
    if (resort) sort();

    return res;
}

template <typename CONTENT>
std::list<CONTENT*> Layer<CONTENT>::getByCoords(const sf::Vector2i& coords,
                                                const VMap& map) {
    std::list<CONTENT*> res;
    const auto end = m_content.end();
    for (auto iter = m_content.begin(); iter != end; ++iter) {
        auto pos = iter->getPosition();
        sf::Vector2i c = map.mapPixelToCoords(pos.x, pos.y);
        if (c == coords) {
            res.emplace_back(&(*iter));
        }
    }
    return res;
}

template <typename CONTENT>
bool Layer<CONTENT>::remove(const CONTENT* content_ptr, bool resort) {
    auto iter = std::find_if(m_content.begin(), m_content.end(),
                             [content_ptr](const CONTENT& content) {
                                 return &content == content_ptr;
                             });
    if (iter != m_content.end()) {
        m_content.erase(iter);

        if (resort) sort();
        return true;
    } else {
        return false;
    }
}

template <typename CONTENT>
void Layer<CONTENT>::sort() {
    m_content.sort([](const CONTENT& lhs, const CONTENT& rhs) {
        auto lpos = lhs.getPosition();
        auto rpos = rhs.getPosition();
        return (lpos.y < rpos.y) || (lpos.y == rpos.y && lpos.x < rpos.x);
    });
}

template <typename CONTENT>
void Layer<CONTENT>::draw(sf::RenderTarget& target, sf::RenderStates states,
                          const sf::FloatRect& viewport) {
    if (m_is_static) {
        if (m_last_viewport != viewport) {
            sf::Vector2u size(viewport.width + 0.5, viewport.height + 0.5);
            if (m_render_texture.getSize() != size) {
                m_render_texture.create(size.x, size.y);
                m_sprite.setTexture(m_render_texture.getTexture(), true);
            }

            m_render_texture.setView(sf::View(viewport));

            m_render_texture.clear();
            auto end = m_content.end();
            for (auto it = m_content.begin(); it != end; ++it) {
                CONTENT& content = *it;
                auto pos = content.getPosition();
                if (viewport.contains(pos.x, pos.y)) {
                    m_render_texture.draw(content);
                }
            }
            m_render_texture.display();
            m_last_viewport = viewport;
            m_sprite.setPosition(viewport.left, viewport.top);
        }
        target.draw(m_sprite, states);
    } else {
        auto end = m_content.end();
        for (auto it = m_content.begin(); it != end; ++it) {
            const CONTENT& content = *it;
            auto pos = content.getPosition();
            if (viewport.contains(pos.x, pos.y)) {
                target.draw(content, states);
            }
        }
    }
}

template <typename CONTENT>
Layer<CONTENT*>::Layer(const std::string& type, int z, bool is_static)
    : VLayer(type, z, is_static) {}

template <typename CONTENT>
CONTENT* Layer<CONTENT*>::Add(CONTENT* content, bool resort) {
    m_content.emplace_back(content);
    CONTENT* res = m_content.back();
    if (resort) sort();

    return res;
}

template <typename CONTENT>
std::list<CONTENT*> Layer<CONTENT*>::getByCoords(const sf::Vector2i& coords,
                                                 const VMap& map) {
    std::list<CONTENT*> res;
    const auto end = m_content.end();
    for (auto iter = m_content.begin(); iter != end; ++iter) {
        auto pos = (*iter)->getPosition();
        sf::Vector2i c = map.mapPixelToCoords(pos.x, pos.y);
        if (c == coords) {
            res.emplace_back(*iter);
        }
    }
    return res;
}

template <typename CONTENT>
bool Layer<CONTENT*>::remove(const CONTENT* content_ptr, bool resort) {
    auto iter = std::find_if(m_content.begin(), m_content.end(), content_ptr);
    if (iter != m_content.end()) {
        m_content.erase(iter);

        if (resort) sort();
        return true;
    } else {
        return false;
    }
}

template <typename CONTENT>
void Layer<CONTENT*>::sort() {
    m_content.sort([](const CONTENT* lhs, const CONTENT* rhs) {
        auto lpos = lhs->getPosition();
        auto rpos = rhs->getPosition();
        return (lpos.y < rpos.y) || (lpos.y == rpos.y && lpos.x < rpos.x);
    });
}

template <typename CONTENT>
void Layer<CONTENT*>::draw(sf::RenderTarget& target, sf::RenderStates states,
                           const sf::FloatRect& viewport) {
    if (m_is_static) {
        if (m_last_viewport != viewport) {
            sf::Vector2u size(viewport.width + 0.5, viewport.height + 0.5);
            if (m_render_texture.getSize() != size) {
                m_render_texture.create(size.x, size.y);
                m_sprite.setTexture(m_render_texture.getTexture(), true);
            }

            m_render_texture.setView(sf::View(viewport));

            m_render_texture.clear();
            auto end = m_content.end();
            for (auto it = m_content.begin(); it != end; ++it) {
                CONTENT& content = *(*it);
                auto pos = content.getPosition();
                if (viewport.contains(pos.x, pos.y)) {
                    m_render_texture.draw(content);
                }
            }
            m_render_texture.display();
            m_last_viewport = viewport;
            m_sprite.setPosition(viewport.left, viewport.top);
        }
        target.draw(m_sprite, states);
    } else {
        auto end = m_content.end();
        for (auto it = m_content.begin(); it != end; ++it) {
            const CONTENT& content = *(*it);
            auto pos = content.getPosition();
            if (viewport.contains(pos.x, pos.y)) target.draw(content, states);
        }
    }
}

}  // namespace foggy

#endif /* LAYER_H */
