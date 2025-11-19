#ifndef I_HUI_STATE
#define I_HUI_STATE

#include "dr4/window.hpp"
#include "hui/widget.hpp"

namespace hui {

class State {

public:

    // TODO
    
    void ReportHover(Widget *w);
    dr4::Window *GetWindow() const;

};

}; // namespace hui

#endif // I_HUI_STATE
