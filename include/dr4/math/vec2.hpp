#ifndef I_DR4_MATH_VEC2
#define I_DR4_MATH_VEC2

namespace dr4 {

struct Vec2f {

    float x, y;

    Vec2f() 
        :x(0), y(0) {}

    Vec2f(float x_, float y_)
        :x(x_), y(y_) {}

    inline Vec2f operator-() { return Vec2f(-x, -y); }
    inline Vec2f operator+(Vec2f other) { return Vec2f(x + other.x, y + other.y); }
    inline Vec2f operator-(Vec2f other) { return Vec2f(x - other.x, y - other.y); }
    inline Vec2f operator*(float k) { return Vec2f(x * k, y * k); }
    inline Vec2f operator/(float k) { return Vec2f(x / k, y / k); }

    Vec2f Clamped(Vec2f min, Vec2f max) const;
};

}; // namespace dr4

#endif // I_DR4_VEC2
