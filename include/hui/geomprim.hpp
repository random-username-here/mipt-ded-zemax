#ifndef I_HUI_GEOMPRIM
#define I_HUI_GEOMPRIM

#include "dr4/texture.hpp"
#include "hui/event.hpp"

namespace hui {

class GeomPrim: public dr4::Drawable {

public:

    virtual EventResult OnMouseMove(const MouseMoveEvent& evt)    = 0;
    virtual EventResult OnMouseDown(const MouseDownEvent& evt)    = 0;
    virtual EventResult OnMouseRelease(const MouseUpEvent& evt) = 0;
};

};

#endif
