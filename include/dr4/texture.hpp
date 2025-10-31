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
    float borderThickness = 0;
    Color borderColor = Color(255, 0, 0, 255);

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
    Color color = Color(255, 0, 0, 255);
    float fontSize = 20;
    VAlign valign = VAlign::TOP;

    // TODO: return of GetBounds()?
    // virtual Rect2f GetBounds() const = 0;

};

class Image
{
    Image(unsigned width, unsigned height);

    virtual void SetPixel(unsigned x, unsigned y, dr4::Color col) = 0;
    virtual dr4::Color GetPixel(unsigned x, unsigned y) const = 0;
};

class Texture {

public:

    virtual void SetSize(Vec2f size) = 0;
    virtual Vec2f GetSize() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    virtual void Draw(const Rectangle &rect) = 0;
    virtual void Draw(const Text &text) = 0;
    virtual void Draw(const Image &img) = 0;
    virtual void Draw(const Texture &texture, const Vec2f &pos) = 0;

    inline virtual ~Texture() {};
};

}; // namespace dr4

#endif // I_DR4_TEXTURE
