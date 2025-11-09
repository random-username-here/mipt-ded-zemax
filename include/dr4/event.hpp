#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include <cstdint>
#include <string>

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
        // utf8-encoded
        std::string unicode;
    };

    struct MouseMove {
        Vec2f pos;
        Vec2f rel;
    };

    struct MouseButton {
        MouseButtonType button;
        Vec2f pos;
    };

    struct MouseWheel {

        /**
         * The amount scrolled horizontally,
         * positive to the right and negative to the left.
         */
        float deltaX;

        /**
         * The amount scrolled vertically,
         * positive away from the user and negative toward the user.
         */
        float deltaY;

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
