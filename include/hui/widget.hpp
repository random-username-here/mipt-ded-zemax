#ifndef I_HUI_WIDGET
#define I_HUI_WIDGET

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "hui/event.hpp"

namespace hui {

class State;

class Widget : public dr4::Drawable {

protected:

    dr4::Vec2f relPos; ///< Relative to parent
    Widget *parent = nullptr;
    State *const state;
    dr4::Texture *const texture;
    bool textureIsInvalid;

    /// Redraws widget's texture
    virtual void Redraw() = 0;

    EventResult OnMouseDown(MouseDownEvent &evt);
    /// TODO : ... other handlers

public:

    Widget(State *state);

    // REVIEW : move implementations to cpp files?
    
    dr4::Vec2f GetRelPos() const { return relPos; };
    virtual void SetRelPos(dr4::Vec2f pos) { relPos = pos; };

    dr4::Vec2f GetSize() const { return texture->GetSize(); }
    virtual void SetSize(dr4::Vec2f size) { texture->SetSize(size); }

    virtual Widget *GetParent() const { return parent; };
    virtual void SetParent(Widget *parent_) { parent = parent_; }

    void DrawOn(dr4::Texture &texture) override {
        if (textureIsInvalid) {
            Redraw();
            textureIsInvalid = false;
        }
        texture.Draw(texture, relPos);
    }
};

}; // namespace hui

#endif // I_HUI_WIDGET
