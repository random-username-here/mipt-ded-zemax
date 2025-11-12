#ifndef I_DR4_MATH_COLOR
#define I_DR4_MATH_COLOR

#include <cstdint>

namespace dr4 {

struct Color {

    static constexpr uint8_t ColorMaxValue = 255;

    uint8_t r, g, b, a;

    Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_=ColorMaxValue)
        :r(r_), g(g_), b(b_), a(a_) {}

    Color()
        :r(0), g(0), b(0), a(ColorMaxValue) {}

    static const Color White;
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Transparent;
};

inline const Color Color::Transparent = {0, 0, 0, 0};

inline const Color Color::White = { 255, 255, 255 };
inline const Color Color::Black = { 0,     0,   0 };
inline const Color Color::Red   = { 255,   0,   0 };
inline const Color Color::Green = { 0,   255,   0 };
inline const Color Color::Blue  = { 0,     0, 255 };

}; // namespace dr4

#endif // I_DR4_COLOR
