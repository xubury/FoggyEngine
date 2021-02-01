#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "ActionSystem/ActionTarget.hpp"
#include "Configuration/Configuration.hpp"
#include "EntitySystem/ES.hpp"

namespace foggy {
namespace component {

struct Controller : es::Component<Controller, es::DefaultEntity>,
                    foggy::ActionTarget<int> {
   public:
    Controller(foggy::ActionMap<int> &map) : foggy::ActionTarget<int>(map) {}
};
}  // namespace component

}  // namespace foggy

#endif /* CONTROLLER_HPP */
