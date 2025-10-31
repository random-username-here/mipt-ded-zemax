#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include <cstdint>
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

    struct KeyEvent {
        uint32_t type;
        uint8_t state;
        int32_t sym;
        uint16_t mod;
    };

    Type type;

    union {
        MouseMove   mouseMove;
        MouseButton mouseDown;
        MouseButton mouseUp;
        MouseWheel  mouseWheel;
    };
};

};

#endif // I_DR4_EVENT
