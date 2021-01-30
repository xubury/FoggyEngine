#ifndef VLAYOUT_HPP
#define VLAYOUT_HPP

#include "GUI/Layout.hpp"

namespace foggy {
namespace gui {

class VLayout : public Layout {
   public:
    VLayout(const VLayout &) = delete;
    VLayout &operator=(const VLayout &) = delete;
    VLayout(Widget *parent = nullptr);
    ~VLayout();

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

#endif  // VLAYOUT_HPP