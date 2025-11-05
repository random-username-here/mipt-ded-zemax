#ifndef I_DR4_MATH_RECT
#define I_DR4_MATH_RECT

#include "dr4/math/vec2.hpp"

namespace dr4 {

struct Rect2f {

    Vec2f pos, size;

    Rect2f() = default;

    Rect2f(Vec2f pos_, Vec2f size_)
        :pos(pos_), size(size_) {}

    Rect2f(float x, float y, float width, float height)
        :pos(Vec2f(x, y)), size(Vec2f(width, height)) {}

    bool Contains(Vec2f point) const;
};

}; // namespace dr4

#endif // I_DR4_MATH_RECT
