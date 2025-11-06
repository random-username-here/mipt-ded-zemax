#ifndef I_DR4_TEXTURE
#define I_DR4_TEXTURE

#include <string>

#include "dr4/math/color.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/math/vec2.hpp"
#include "math/color.hpp"

namespace dr4 {

struct Rectangle {

public:

    virtual ~Rectangle() = default;

    virtual void SetRect(const Rect2f &rect) = 0;
    virtual void SetFill(const Color &color) = 0;
    virtual void SetBorderThickness(float thickness) = 0;
    virtual void SetBorderColor(const Color &color) = 0;

    // NOTE(i-s-d): this probbably should not have getters,
    //              this thing should only be used for drawing things.
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
    virtual float GetAscent(float fontSize) = 0;

    /**
     * Get distance from baseline to bottoms of the hanging letters, like `y`.
     * This value is **negative** for most fonts (because letters descend
     * below baseline).
     */
    virtual float GetDescent(float fontSize) = 0;
};

class Text {

public:

    virtual ~Text() = default;

    enum class VAlign {
        UNKNOWN = -1,
        TOP,
        MIDDLE,
        BASELINE,
        BOTTOM
    };

    virtual void SetPos(Vec2f pos) = 0;
    virtual void SetText(const std::string &text) = 0;
    virtual void SetColor(const Color &color) = 0;
    virtual void SetFontSize(float size) = 0;
    virtual void SetVAlign(VAlign align) = 0;
    virtual void SetFont(const Font *font) = 0;

    virtual float GetWidth() const = 0;
};


class Image {

public:
    virtual ~Image() = default;

    virtual void SetPixel(unsigned x, unsigned y, Color color) = 0;
    virtual Color GetPixel(unsigned x, unsigned y) const = 0;

    virtual void SetSize(Vec2f size) = 0;
    virtual Vec2f GetSize() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;
};

class Texture {

public:
    virtual ~Texture() = default;

    virtual void SetSize(Vec2f size) = 0;
    virtual Vec2f GetSize() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    virtual void Clear(Color color) = 0;

    virtual void Draw(const Rectangle &rect) = 0;
    virtual void Draw(const Text &text) = 0;
    virtual void Draw(const Image &img, const Vec2f &pos) = 0;
    virtual void Draw(const Texture &texture, const Vec2f &pos) = 0;
};

}; // namespace dr4

#endif // I_DR4_TEXTURE
