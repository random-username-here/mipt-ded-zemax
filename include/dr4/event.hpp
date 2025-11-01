#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include "dr4/math/vec2.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/mousecodes.hpp"

namespace dr4 {

struct Event {

    enum class Type {
        UNKNOWN = -1,
        KEY_DOWN,
        KEY_UP,
        MOUSE_MOVE,
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_WHEEL,
        QUIT
    };

    struct MouseMove {
        Vec2f pos;
        Vec2f rel;
    };

    struct MouseButton {
        MouseCode button;
        Vec2f pos;
    };

    struct MouseWheel {
        int delta;
        Vec2f pos;
    };

    struct KeyButton {
        KeyCode sym;
        KeyMode mod;
    };

    Type type;

    union {
        MouseMove   mouseMove;
        MouseButton mouseButton;
        MouseWheel  mouseWheel;
        KeyButton   keyDown;
        KeyButton   keyUp;
    };
};

};

#endif // I_DR4_EVENT
