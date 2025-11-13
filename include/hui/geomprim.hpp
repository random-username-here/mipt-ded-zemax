#ifndef I_HUI_GEOMPRIM
#define I_HUI_GEOMPRIM

#include "dr4/event.hpp"
#include "dr4/texture.hpp"

namespace hui {

class GeomPrim: public dr4::Drawable {

public:

    virtual bool OnMouseMove(const dr4::Event& event)    = 0;
    virtual bool OnMouseDown(const dr4::Event& event)    = 0;
    virtual bool OnMouseRelease(const dr4::Event& event) = 0;
};

};

#endif
