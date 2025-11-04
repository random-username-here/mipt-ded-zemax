#ifndef I_DR4_EVENT
#define I_DR4_EVENT

#include "dr4/math/vec2.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/mousecodes.hpp"
#include <variant>
#include <cstdint>

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
        WINDOW_RESIZED,
        QUIT
    };

    struct MouseMove {
        Vec2f pos;
        Vec2f rel;
        bool pressedButtons[3];
    };

    struct MouseButton {
        MouseCode button;
        Vec2f pos;
        uint8_t clicks;
    };

    struct MouseWheel {
        Vec2f delta;
        Vec2f pos;
    };

    struct KeyButton {
        KeyCode sym;
        KeyMode mod;
        bool repeat;
    };

    struct WindowResized {
        Vec2f newSize;
    };

    Type type;
    
    std::variant< // -std=c++17
        MouseMove,
        MouseButton,
        MouseWheel,
        KeyButton,
        WindowResized
    > data;

    Event() = default;
    Event(MouseMove move) : type(Type::MOUSE_MOVE), data(move) {}
    Event(MouseButton btn) : type(Type::MOUSE_DOWN), data(btn) {}
    Event(KeyButton key) : type(Type::KEY_DOWN), data(key) {}
    Event(WindowResized resize) : type(Type::WINDOW_RESIZED), data(resize) {}
    
    template<typename T>
    bool Is() const { return std::holds_alternative<T>(data); }
    
    template<typename T>
    const T& Get() const { return std::get<T>(data); }
};

} // namespace dr4

#endif