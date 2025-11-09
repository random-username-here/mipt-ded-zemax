#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include "dr4/math/vec2.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/mouse_buttons.hpp"

namespace dr4 {

struct Event {

    enum class Type {
        UNKNOWN = 0,
        KEY_DOWN,
        KEY_UP,
        MOUSE_MOVE,
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_WHEEL,
        TEXT_EVENT,
        QUIT
    };

    struct TextEvent {
        uint32_t unicode;
    };

    struct MouseMove {
        Vec2f pos;
        Vec2f rel;
    };

    struct MouseButton {
        dr4::MouseButtonType button;
        Vec2f pos;
    };

    struct MouseWheel {
        int delta;
        Vec2f pos;
    };

    struct KeyEvent {
        KeyCode sym;
        uint16_t mods;
    };

    Type type;

    union {
        TextEvent   text;
        MouseMove   mouseMove;
        MouseButton mouseButton;
        MouseWheel  mouseWheel;
        KeyEvent    key;
    };

    Event() {}
};

};

#endif // I_DR4_EVENT
