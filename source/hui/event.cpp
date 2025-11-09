#include "hui/event.hpp"
#include "hui/widget.hpp"

hui::EventResult hui::MouseDownEvent::Apply(hui::Widget &widget) {
    return widget.OnMouseDown(*this);
}

hui::EventResult hui::MouseUpEvent::Apply(hui::Widget &widget) {
    return widget.OnMouseUp(*this);
}

hui::EventResult hui::MouseMoveEvent::Apply(hui::Widget &widget) {
    return widget.OnMouseMove(*this);
}

hui::EventResult hui::KeyPressedEvent::Apply(hui::Widget &widget) {
    return widget.OnKeyPressed(*this);
}

hui::EventResult hui::TextEnterEvent::Apply(hui::Widget &widget) {
    return widget.OnTextEnter(*this);
}

hui::EventResult hui::IdleEvent::Apply(hui::Widget &widget) {
    return widget.OnIdle(*this);
}
