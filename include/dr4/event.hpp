#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include "dr4/math/vec2.hpp"
#include "dr4/keycodes.hpp"

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
        int button;
        bool pressed;
        Vec2f pos;
    };

    struct MouseWheel {
        int delta;
        Vec2f pos;
    };

    struct KeyEvent {
        dr4::KeySyms sym;
        dr4::KeyModes mod;
    };

    Type type;

    union {
        MouseMove   mouseMove;
        MouseButton mouseButton;
        MouseWheel  mouseWheel;
        KeyEvent    keyDown;
        KeyEvent    KeyUp;
    };
};

};

#endif // I_DR4_EVENT
