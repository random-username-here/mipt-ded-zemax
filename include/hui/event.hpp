#ifndef I_HUI_EVENT
#define I_HUI_EVENT

#include <stdint.h>

#include "dr4/math/vec2.hpp"
#include "dr4/keycodes.hpp"

namespace hui {

enum class EventResult {
    UNHANDLED, HANDLED
};

class Widget;

struct Event {
    virtual EventResult Apply(Widget &widget) = 0;
};

struct MouseDownEvent : public Event {

    dr4::Vec2f relPos;
    virtual EventResult Apply(Widget &widget) override; // TODO: implement

};

struct MouseUpEvent : public Event {

    dr4::Vec2f relPos;
    virtual EventResult Apply(Widget &widget) override; // TODO: implement

};

struct MouseMoveEvent : public Event {

    dr4::Vec2f rel;
    virtual EventResult Apply(Widget &widget) override; // TODO: implement

};

struct KeyPressed : public Event {

    dr4::KeyCode sym;
    uint16_t mod;

    virtual EventResult Apply(Widget &widget) override; // TODO: implement

};

struct IdleEvent : public Event {

    /// Time from some point of reference, used for deadlines, ....
    /// In seconds.
    double absTime;

    /// Time from previous IdleEvent, in seconds.
    double deltaTime;

    virtual EventResult Apply(Widget &widget) override; // TODO: implement
};

// TODO: other events
// MouseUpEvent, MouseMoveEvent, ..., IdleEvent

};

#endif
