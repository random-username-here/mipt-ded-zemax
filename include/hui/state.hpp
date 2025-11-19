#ifndef I_HUI_STATE
#define I_HUI_STATE

#include "dr4/window.hpp"
#include "hui/widget.hpp"

namespace hui {

class State {
    dr4::Window *window_;
public:
    State(dr4::Window *window): window_(window) {};
    void ReportHover(Widget *w);
    dr4::Window *GetWindow() const { return window_; }
};

}; // namespace hui

#endif // I_HUI_STATE
