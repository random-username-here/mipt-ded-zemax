#ifndef I_HUI_WIDGET
#define I_HUI_WIDGET

#include "vec2.hpp"
#include "texture.hpp"
#include "event.hpp"

namespace hui {

class State;

class Widget {

protected:

    dr4::Vec2f relPos; ///< Relative to parent
    Widget *parent = nullptr;
    State *const state;
    bool textureIsInvalid;

    dr4::Vec2f size;

public:
    dr4::Texture *texture; // *const
    /// Redraws widget's texture
    virtual void Redraw() = 0;

    virtual EventResult OnIdle(IdleEvent &evt);
    virtual EventResult OnMouseDown(MouseDownEvent &evt);
    /// TODO : ... other handlers

public:

    Widget(hui::State *state);
    Widget(hui::State *state, dr4::Vec2f pos, dr4::Vec2f size);
    
    dr4::Vec2f GetRelPos() const;
    virtual void SetRelPos(dr4::Vec2f pos);

    dr4::Vec2f GetSize() const;
    virtual void SetSize(dr4::Vec2f size);

    virtual Widget *GetParent() const;
    virtual void SetParent(Widget *parent_);

    void DrawOn(dr4::Texture &texture);
};

}; // namespace hui

#endif // I_HUI_WIDGET
