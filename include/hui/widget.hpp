#ifndef I_HUI_WIDGET
#define I_HUI_WIDGET
#include <memory>

#include "dr4/math/vec2.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/texture.hpp"
#include "hui/data.hpp"
#include "hui/event.hpp"

namespace hui {

class UI;
class Container;
class Event;

/**
 * @brief A widget
 *
 * This represents a generic widget. This does not include
 * child support (see Container for that).
 *
 * @todo A rectangle to set background/border of the widget?
 * @todo Style sheets?
 */
class Widget : public dr4::Drawable {

    /**
     * @name Management
     */
    /// @{

    friend class Container;
    friend class UI;

private:
    Widget *parent = nullptr;
    UI *const ui;

    /// Set this widget's parent
    /// This is used by Container's BecomeParentOf()
    void SetParent(Widget *parent_);

public:

    Widget(UI *ui_);
    virtual ~Widget();

    Widget *GetParent() const;
    UI *GetUI() const;

    /// @}
    //--------------------------------------------------------------------------
    /**
     * @name Positioning
     */
    /// @{

private:

    dr4::Rect2f rect;

protected:

    /// Called when someone set's widget's size
    virtual void OnSizeChanged();

public:

    inline void SetSize(float x, float y) { SetSize(dr4::Vec2f(x, y)); }
    void SetSize(dr4::Vec2f size);
    dr4::Vec2f GetSize() const;

    void SetPos(float x, float y) { SetPos(dr4::Vec2f(x, y)); }
    void SetPos(dr4::Vec2f pos) override final;
    dr4::Vec2f GetPos() const override final;

    void SetRect(dr4::Rect2f rect);
    dr4::Rect2f GetRect() const;


    virtual dr4::Vec2f GetAbsolutePos() const;


    /// @}
    //--------------------------------------------------------------------------
    /**
     * @name Drawing
     */
    /// @{

private:

    const std::unique_ptr<dr4::Texture> texture;

    /// If true, Redraw() will be called inside next DrawOn()
    /// Because DrawOn() has const, this must be mutable.
    mutable bool textureWillRedraw = true;

    /// How much texture sticks out of the widget
    BorderMapped<float> extents;

protected:

    dr4::Texture &GetTexture() const;
    void SetTextureExtents(BorderMapped<float> extents_);
    const BorderMapped<float> &GetTextureExtents() const;

    /**
     * @brief Redraw what is on the texture.
     * There is no guarantee what image drawn previous time survived.
     * Don't forget to call `ForceRedraw()` when you're done.
     */
    virtual void Redraw() const;

public:
    dr4::Texture &GetFreshTexture();

    void DrawOn(dr4::Texture &texture) const override final;
    void ForceRedraw();

    /// @}
    //--------------------------------------------------------------------------
    /**
     * @name Events
     *
     * Remember to call those function for parent class when inheriting!
     * Some of them do important stuff, like set currently hovered widget
     * or propogate that event to children.
     *
     * Widgets are opaque to events by default. So widget will
     * take block all mouse events from going to widgets bellow.
     * This behaviour can be changed by overriding those event handlers.
     *
     * KeyDown/KeyUp/Text events are triggered only for focused widgets.
     * Focused = will do something with those keypresses, like move
     * or enter text. Focus != highlighted, like current window.
     * Those ones we call "active", and how they behave is not related
     * to focus.
     *
     * Widgets are not automatically set as focused. To do that
     * they must do SetFocused(this) on their state.
     *
     */
    /// @{

    friend class MouseButtonEvent;
    friend class MouseMoveEvent;
    friend class MouseWheelEvent;
    friend class KeyEvent;
    friend class TextEvent;
    friend class IdleEvent;

protected:

    virtual void OnHoverGained();
    virtual void OnHoverLost();
    virtual void OnFocusGained();
    virtual void OnFocusLost();

    virtual EventResult OnMouseDown(MouseButtonEvent &evt);
    virtual EventResult OnMouseUp(MouseButtonEvent &evt);
    virtual EventResult OnMouseMove(MouseMoveEvent &evt);
    virtual EventResult OnMouseWheel(MouseWheelEvent &evt);
    virtual EventResult OnKeyDown(KeyEvent &evt);
    virtual EventResult OnKeyUp(KeyEvent &evt);
    virtual EventResult OnText(TextEvent &evt);

    virtual EventResult OnIdle(IdleEvent &evt);
    /// @}
};

}; // namespace hui

#endif // I_HUI_WIDGET
