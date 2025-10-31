#ifndef I_DR4_TEXTURE
#define I_DR4_TEXTURE

#include <string>

#include "dr4/math/color.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"

namespace dr4 {

struct Rectangle {

    Rect2f rect;
    Color fill;
    float borderThickness;
    Color borderColor;

};

struct Text {

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

    // TODO: return of GetBounds()?
    // virtual Rect2f GetBounds() const = 0;

};

class Texture {

public:

    virtual void SetSize(Vec2f size) = 0;
    virtual Vec2f GetSize() = 0;
    virtual float Width() = 0;
    virtual float Height() = 0;

    virtual void Draw(Rectangle &rect) = 0;
    virtual void Draw(Text &text) = 0;
    virtual void Draw(Texture &texture, const Vec2f &pos) = 0;
};

}; // namespace dr4

#endif // I_DR4_TEXTURE
