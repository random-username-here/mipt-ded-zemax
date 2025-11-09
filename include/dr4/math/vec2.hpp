#ifndef I_DR4_MATH_VEC2
#define I_DR4_MATH_VEC2

namespace dr4 {

struct Vec2f {

    float x, y;

    Vec2f() = default;

    Vec2f(float x_, float y_)
        :x(x_), y(y_) {}

    inline Vec2f operator-() const { return Vec2f(-x, -y); }
    inline Vec2f operator+(const Vec2f &other) const { return Vec2f(x + other.x, y + other.y); }
    inline Vec2f operator-(const Vec2f &other) const { return Vec2f(x - other.x, y - other.y); }
    inline Vec2f operator*(float k) const { return Vec2f(x * k, y * k); }
    inline Vec2f operator/(float k) const { return Vec2f(x / k, y / k); }

    inline Vec2f& operator+=(const Vec2f &other) { x += other.x; y += other.y; return *this; }
    inline Vec2f& operator-=(const Vec2f &other) { x -= other.x; y -= other.y; return *this; }
    inline Vec2f& operator*=(float k) { x *= k; y *= k; return *this; }
    inline Vec2f& operator/=(float k) { x /= k; y /= k; return *this; }

    Vec2f Clamped(const Vec2f &min, const Vec2f &max) const;
};

inline Vec2f operator*(float k, const Vec2f& vec) {
    return Vec2f(vec.x * k, vec.y * k);
}

}; // namespace dr4

#endif // I_DR4_VEC2