#ifndef I_DR4_TEXTURE
#define I_DR4_TEXTURE

#include <string>

#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/math/rect.hpp"

namespace dr4 {

class Texture;

class Drawable {

public:

    virtual ~Drawable() = default;

    virtual void DrawOn(Texture& texture) const = 0;

    virtual void SetPos(Vec2f pos) = 0;

    virtual Vec2f GetPos() const = 0;
};


class Line: public Drawable {

public:

    virtual void SetStart(Vec2f start) = 0;
    virtual void SetEnd(Vec2f end) = 0;
    virtual void SetColor(Color color) = 0;
    virtual void SetThickness(float thickness) = 0;

    virtual Vec2f GetStart() const = 0;
    virtual Vec2f GetEnd() const = 0;
    virtual Color GetColor() const = 0;
    virtual float GetThickness() const = 0;
};

class Circle: public Drawable {

public:

    virtual void SetCenter(Vec2f center) = 0;
    virtual void SetRadius(float radius) = 0;
    virtual void SetFillColor(Color color) = 0;
    virtual void SetBorderColor(Color color) = 0;
    virtual void SetBorderThickness(float thickness) = 0;

    virtual Vec2f GetCenter() const = 0;
    virtual float GetRadius() const = 0;
    virtual Color GetFillColor() const = 0;
    virtual Color GetBorderColor() const = 0;
    virtual float GetBorderThickness() const = 0;
};

class Rectangle: public Drawable {

public:

    virtual ~Rectangle() = default;

    virtual void SetSize(Vec2f size) = 0;
    virtual void SetFillColor(Color color) = 0;
    virtual void SetBorderThickness(float thickness) = 0;
    virtual void SetBorderColor(Color color) = 0;

    virtual Vec2f GetSize() const = 0;
    virtual Color GetFillColor() const = 0;
    virtual float GetBorderThickness() const = 0;
    virtual Color GetBorderColor() const = 0;
};

class Font {

public:

    virtual ~Font() = default;

    virtual void LoadFromFile(const std::string &path) = 0;
    virtual void LoadFromBuffer(const void *buffer, size_t size) = 0;

    /**
     * Get distance from the baseline (line on top of which letters are placed)
     * to the tops of the capital letters.
     */
    virtual float GetAscent(float fontSize) const = 0;

    /**
     * Get distance from baseline to bottoms of the hanging letters, like `y`.
     * This value is **negative** for most fonts (because letters descend
     * below baseline).
     */
    virtual float GetDescent(float fontSize) const = 0;
};

class Text: public Drawable {

public:

    virtual ~Text() = default;

    enum class VAlign {
        UNKNOWN = -1,
        TOP,
        MIDDLE,
        BASELINE,
        BOTTOM
    };

    virtual void SetText(const std::string &text) = 0;
    virtual void SetColor(Color color) = 0;
    virtual void SetFontSize(float size) = 0;
    virtual void SetVAlign(VAlign align) = 0;
    virtual void SetFont(const Font *font) = 0;

    virtual Rect2f             GetBounds() const = 0;
    virtual const std::string &GetText() const = 0;
    virtual Color              GetColor() const = 0;
    virtual float              GetFontSize() const = 0;
    virtual VAlign             GetVAlign() const = 0;
    virtual const Font        &GetFont() const = 0;
};


class Image: public Drawable {

public:
    virtual ~Image() = default;

    virtual void SetPixel(size_t x, size_t y, Color color) = 0;
    virtual Color GetPixel(size_t x, size_t y) const = 0;

    virtual void SetSize(Vec2f size) = 0;

    virtual Vec2f GetSize() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;
};

class Texture: public Drawable {

public:
    virtual ~Texture() = default;

    virtual void SetSize(Vec2f size) = 0;
    virtual Vec2f GetSize() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    virtual void Clear(Color color) = 0;

    virtual void Draw(const Drawable& drawable) {
        drawable.DrawOn(*this);
    }
};

}; // namespace dr4

#endif // I_DR4_TEXTURE
