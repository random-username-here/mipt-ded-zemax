#ifndef I_HUI_MATH_COLOR
#define I_HUI_MATH_COLOR

#include <cstdint>

namespace dr4 {

struct Color {

    uint8_t r, g, b, a;

    inline Color() : r(0), g(0), b(0), a(0) {};
    inline Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        :r(r), g(g), b(b), a(a) {}
};

}; // namespace hui

#endif // I_HUI_COLOR
