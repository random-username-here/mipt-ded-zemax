#ifndef I_HUI_GEOMPRIM
#define I_HUI_GEOMPRIM

#include "dr4/texture.hpp"
#include "hui/event.hpp"

namespace hui {

class GeomPrim: public dr4::Drawable {
public:
    virtual EventResult OnMouseMove()    = 0;
    virtual EventResult OnMouseDown()    = 0;
    virtual EventResult OnMouseRelease() = 0;
}

};

#endif
