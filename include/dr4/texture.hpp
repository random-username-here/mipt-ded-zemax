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

class Font {

public:

    virtual void loadFromFile(const std::string& path) = 0;
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
    const Font *font;

    Rect2f GetBounds() const;
};

class Texture {

public:

    virtual void SetSize(Vec2f size) = 0;
    virtual Vec2f GetSize() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    virtual void Draw(const Rectangle &rect) = 0;
    virtual void Draw(const Text &text) = 0;
    virtual void Draw(const Texture &texture, const Vec2f &pos) = 0;

    virtual ~Texture() = default;
};

}; // namespace dr4

#endif // I_DR4_TEXTURE
