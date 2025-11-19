#include "hui/event.hpp"
#include "hui/widget.hpp"

namespace hui {

EventResult MouseButtonEvent::Apply(Widget &widget) {
    if (pressed)
        return widget.OnMouseDown(*this);
    else
        return widget.OnMouseUp(*this);
}

EventResult MouseMoveEvent::Apply(Widget &widget) {
    return widget.OnMouseMove(*this);
}

EventResult MouseWheelEvent::Apply(Widget &widget) {
    return widget.OnMouseWheel(*this);
}

EventResult KeyEvent::Apply(Widget &widget) {
    if (pressed)
        return widget.OnKeyDown(*this);
    else
        return widget.OnKeyUp(*this);
}

EventResult TextEvent::Apply(Widget &widget) {
    return widget.OnText(*this);
}

EventResult IdleEvent::Apply(Widget &widget) {
    widget.OnIdle(*this);
    return EventResult::HANDLED;
}

};
