#ifndef I_HUI_MATH_VEC2
#define I_HUI_MATH_VEC2

namespace dr4 {

// TODO : do not use references for vec2
struct Vec2f {

    float x, y;

    Vec2f(float x, float y) 
        :x(x), y(y) {}

    inline Vec2f operator-() { return Vec2f(-x, -y); }
    inline Vec2f operator+(const Vec2f &other) { return Vec2f(x + other.x, y + other.y); }
    inline Vec2f operator-(const Vec2f &other) { return Vec2f(x - other.x, y - other.y); }
    inline Vec2f operator*(float k) { return Vec2f(x * k, y * k); }
    inline Vec2f operator/(float k) { return Vec2f(x / k, y / k); }

    Vec2f Clamped(const Vec2f &min, const Vec2f &max) const;
};

}; // namespace hui

#endif // I_HUI_VEC2
