#ifndef I_DR4_WINDOW
#define I_DR4_WINDOW

#include <string>
#include <optional>

#include "dr4/event.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

namespace dr4 {

class Window {

public:

	virtual ~Window() = default;

    virtual void SetTitle(const std::string &title) = 0;
    virtual const std::string &GetTitle() const = 0;

    virtual Vec2f GetSize() const = 0;
    virtual void SetSize(Vec2f size) = 0;

    virtual void Open() = 0;
    virtual bool IsOpen() const = 0;
    virtual void Close() = 0;

    virtual void Clear(Color color) = 0;
    virtual void Draw(const Texture &texture, Vec2f pos) = 0;
    virtual void Display() = 0;

    // Monotonic time in ms
    virtual double GetTime() = 0;

    virtual Texture   *CreateTexture()   = 0;
    virtual Image     *CreateImage()     = 0;
    virtual Font      *CreateFont()      = 0;
    virtual Line      *CreateLine()      = 0;
    virtual Circle    *CreateCircle()    = 0;
    virtual Rectangle *CreateRectangle() = 0;
    virtual Text      *CreateText()      = 0;

    /**
     * Start receiving utf8-encoded input.
     * This is for optimization purposes: if implementation doesn't support
     * enabling/disabling text input capturing, leave it a no-op.
     */
    virtual void StartTextInput() = 0;

    /**
     * Stop receiving utf8-encoded input.
     * This is for optimization purposes: if implementation doesn't support
     * enabling/disabling text input capturing, leave it a no-op.
     */
    virtual void StopTextInput() = 0;

    virtual std::optional<Event> PollEvent() = 0;
};

}; // namespace dr4

#endif // I_DR4_WINDOW
