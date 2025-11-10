#ifndef I_HUI_EVENT
#define I_HUI_EVENT

#include "dr4/keycodes.hpp"
#include "dr4/math/vec2.hpp"
#include <cstdint>

namespace hui {

enum class EventResult {
    UNHANDLED, HANDLED
};

class Widget;

struct Event {

    virtual EventResult Apply(Widget &widget) = 0;

};

struct MouseButtonEvent : public Event {

    bool pressed; 
    dr4::Vec2f relPos;

    virtual EventResult Apply(Widget &widget) override;

};

struct MouseMoveEvent : public Event {

    dr4::Vec2f relPos;
    dr4::Vec2f deltaPos;

    virtual EventResult Apply(Widget &widget) override;

};

struct MouseWheelEvent : public Event {

    dr4::Vec2f relPos;
    dr4::Vec2f scroll;

    virtual EventResult Apply(Widget &widget) override;

};

struct KeyEvent : public Event {

    bool pressed;
    dr4::KeyCode key;
    uint16_t mods; // combination of dr4::KeyMode

    virtual EventResult Apply(Widget &widget) override;

};

struct TextEvent : public Event {

    /// A С-string with utf8-encoded text
    /// TODO: string_view?
    const char *text;

    virtual EventResult Apply(Widget &widget) override;

};

/**
 * @brief Event sent each frame to update stuff
 * 
 * This one ignores event grabbing mechanism, because it
 * seems like that would be a weird thing to do. All OnIdle()
 * handlers should just return HANDLED.
 *
 * @note (i-s-d): but you can prove me wrong
 */
struct IdleEvent : public Event {

    /**
     * @brief Time from some point of reference.
     * Usefull for deadlines, animations, etc. In seconds.
     */
    double absTime;

    /**
     * @brief Time since previous IdleEvent was fired.
     * Usefull for physics simulations, etc. In seconds.
     */
    double deltaTime;

    virtual EventResult Apply(Widget &widget) override; // TODO: implement
};

};

#endif
