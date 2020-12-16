#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include "GUI/Widget.hpp"

namespace foggy {

class Label : public Widget {
   public:
    Label(const std::string &text, const sf::Font &font, const sf::Color &color,
          Widget *parent = nullptr);
    virtual ~Label() = default;

    void SetText(const std::string &text);

    void SetCharacterSize(uint32_t size);
    uint32_t GetCharacterSize() const;

    void SetTextColor(const sf::Color &color);
    sf::Color GetTextColor() const;

    void SetOrigin(float x, float y);

    sf::Vector2f GetSize() const override;

   private:
    sf::Text m_text;
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;
};

}  // namespace foggy

#endif /* LABEL_H */
