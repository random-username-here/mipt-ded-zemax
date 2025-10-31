#ifndef I_DR4_MATH_COLOR
#define I_DR4_MATH_COLOR

#include <cstdint>

namespace dr4 {

struct Color {

    uint8_t r, g, b, a;

    inline Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        :r(r), g(g), b(b), a(a) {}
};

}; // namespace dr4

#endif // I_DR4_COLOR
