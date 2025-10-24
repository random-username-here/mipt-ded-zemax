#ifndef I_HUI_TEXTURE
#define I_HUI_TEXTURE

#include <string>

#include "dr4/math/color.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"

namespace dr4 {

class Texture;

struct Drawable {
    virtual void DrawOn(Texture &texture) = 0;
};

struct Pixel : public Drawable {

    Vec2f pos;
    Color color;

    virtual void DrawOn(Texture &texture) = 0;
};

struct Rectangle : public Drawable {

    Rect2f rect;
    Color fill;
    float borderThickness;
    Color borderColor;

    virtual void DrawOn(Texture &texture) = 0;
};

struct Text : public Drawable {

    enum class VAlign {
        UNKNOWN = -1,
        TOP,
        MIDDLE,
        BASELINE,
        BOTTOM
    };

    const std::string text;
    Vec2f pos;
    Color color;
    float fontSize;
    VAlign valign = VAlign::TOP;

    virtual Rect2f GetBounds() const = 0;

    virtual void DrawOn(Texture &texture) const = 0;
};

class Texture {

public:

    virtual void SetSize(Vec2f size) = 0;
    virtual Vec2f GetSize() = 0;
    virtual float Width() = 0;
    virtual float Height() = 0;

    inline void Draw(Drawable &object) { object.DrawOn(*this); }
    virtual void Draw(Texture &texture, const Vec2f &pos) = 0;
};

}; // namespace hui

#endif // I_HUI_TEXTURE
