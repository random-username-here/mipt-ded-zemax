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
};

}; // namespace dr4

#endif // I_DR4_COLOR
