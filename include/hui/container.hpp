#ifndef I_HUI_CONTAINER
#define I_HUI_CONTAINER

#include "event.hpp"
#include "widget.hpp"

#include <vector>

namespace hui {

class ContainerWidget : public hui::Widget {
public:
    ContainerWidget(hui::State *state, dr4::Vec2f pos, dr4::Vec2f size);
// protected:
    virtual EventResult PropogateToChildren(Event &event) = 0;

    // TODO: reimplement methods using that

};

};

#endif
