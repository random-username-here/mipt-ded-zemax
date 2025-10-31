#ifndef I_HUI_MATH_RECT
#define I_HUI_MATH_RECT

#include "vec2.hpp"

namespace dr4 {

struct Rect2f {

    Vec2f pos, size;

    inline Rect2f(Vec2f pos, Vec2f size) 
        :pos(pos), size(size) {}

    inline Rect2f(float x, float y, float width, float height)
        :pos(Vec2f(x, y)), size(Vec2f(width, height)) {}

    bool Contains(const Vec2f &point) const;
};

}; // namespace hui

#endif // I_HUI_RECT
