#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include <cstdint>
#include "dr4/math/vec2.hpp"
#include "dr4/keycodes.hpp"

namespace dr4 {

struct Event {

    enum class Type {
        MOUSE_MOVE,
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_WHEEL,
        SYM_DOWN,
        SYM_UP,
        QUIT
    };

    struct MouseMove {
        Vec2f pos;
        Vec2f rel;
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

    struct KeyEvent {
        dr4::KeySyms sym;
        dr4::KeyModes mod;
    };

    Type type;

    union {
        MouseMove   mouseMove;
        MouseButton mouseDown;
        MouseButton mouseUp;
        MouseWheel  mouseWheel;
        KeyEvent    SYMDown;
        KeyEvent    SYMUp;
    };
};

};

#endif // I_DR4_EVENT
