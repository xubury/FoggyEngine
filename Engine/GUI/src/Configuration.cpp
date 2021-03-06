#include "GUI/Configuration.hpp"

namespace foggy {
namespace gui {

ActionMap<int> Configuration::default_gui_inputs;
Configuration::__Initializer Configuration::__initializer__;

sf::Color Configuration::Colors::button_fill(86, 20, 19);
sf::Color Configuration::Colors::button_outline(146, 20, 19);
sf::Color Configuration::Colors::label_text(180, 93, 23);
float Configuration::Colors::lighting = 1.4;

unsigned int Configuration::Sizes::button_outline_thickness = 5;
unsigned int Configuration::Sizes::layout_spacing = 10;

void Configuration::initEvents() {
    default_gui_inputs.map(GuiInputs::Escape,
                           Action(sf::Keyboard::Escape, Action::Type::Pressed));
}

void Configuration::init() { initEvents(); }

}  // namespace gui
}  // namespace foggy
