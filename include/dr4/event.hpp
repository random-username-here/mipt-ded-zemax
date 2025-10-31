#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include "dr4/math/vec2.hpp"

namespace dr4 {

struct Event {

    enum class Type {
        MOUSE_MOVE,
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_WHEEL,
        KEY_DOWN,
        KEY_UP
    };

    struct MouseMove {
        Vec2f pos;
    };

    struct MouseButton {
        int button;
        bool pressed;
        Vec2f pos;
    };

    struct MouseWheel {
        Vec2f delta;
        Vec2f pos;
    };

    // TODO: keys

    Type type;

    union {
        MouseMove   mouseMove;
        MouseButton mouseDown;
        MouseButton mouseUp;
        MouseWheel  mouseWheel;
    };

};

};

#endif
