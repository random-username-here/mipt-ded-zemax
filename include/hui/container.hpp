#ifndef I_HUI_CONTAINER
#define I_HUI_CONTAINER

#include "hui/event.hpp"
#include "hui/widget.hpp"

namespace hui {

class ContainerWidget : public Widget {

protected:

    virtual EventResult PropogateToChildren(Event &event) = 0;

    // TODO: reimplement methods using that

};

};

#endif
