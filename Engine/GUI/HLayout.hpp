#ifndef HLAYOUT_HPP
#define HLAYOUT_HPP
#include "GUI/Layout.hpp"

namespace foggy {
namespace gui {

class HLayout : public Layout {
   public:
    HLayout(const HLayout &) = delete;
    HLayout &operator=(const HLayout &) = delete;
    HLayout(Widget *parent = nullptr);
    ~HLayout();

    virtual void clear() override;

    void add(Widget *widget);

    Widget *at(uint32_t index);

    virtual sf::Vector2f getSize() const override;

   protected:
    virtual bool processEvent(const sf::Event &event,
                              const sf::Vector2f &parent_pos) override;
    virtual void processEvents(const sf::Vector2f &parent_pos) override;

   private:
    std::vector<Widget *> m_widgets;
    virtual void updateShape() override;
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;
};

}  // namespace gui
}  // namespace foggy

#endif  // HLAYOUT_H