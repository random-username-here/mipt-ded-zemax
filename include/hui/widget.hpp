#ifndef I_HUI_WIDGET
#define I_HUI_WIDGET

#include "dr4/math/vec2.hpp"
#include "dr4/math/rect.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "hui/event.hpp"

namespace hui {

class Widget;

struct State {
    Widget* hovered;
    Widget* focused;

    dr4::Window* window;
};

class Widget {

protected:

    dr4::Rect2f rect;
    Widget *parent = nullptr;
    State *const state;
    dr4::Texture *const texture;
    bool textureIsInvalid = false;
    bool hidden;

    /// Redraws widget's texture
    virtual void Redraw() {
        if (hidden) {
            return;
        }
        if (parent != NULL) {
            parent->GetTexture()->Draw(*texture);
            texture->Clear(dr4::Color(0, 0, 0));
        }
    };

    void SetHidden(bool hidden_) { hidden = hidden_; };
    bool GetHidden() const { return hidden; };

    virtual void Move(float shift_x, float shift_y) {
        rect.pos.x += shift_x;
        rect.pos.y += shift_y;
    };

    bool IsInside(dr4::Vec2f relPos) const {
        return ((relPos.x < rect.pos.x + rect.size.x)
             && (relPos.y < rect.pos.y + rect.size.y)
             && (relPos.x > rect.pos.x)
             && (relPos.y > rect.pos.y));
    };

    virtual EventResult OnMouseDown(const MouseDownEvent &evt) {
        if (hidden) {
            return EventResult::UNHANDLED;
        }

        if (IsInside(evt.relPos)) {
            state->focused = this;
            return EventResult::HANDLED;
        }
        return EventResult::UNHANDLED;
    };

    virtual EventResult OnMouseRelease(const MouseUpEvent& evt) {
        if (hidden) {
            return EventResult::UNHANDLED;
        }

        if (IsInside(evt.relPos)) {
            return EventResult::HANDLED;
        }

        return EventResult::UNHANDLED;
    };

    virtual EventResult OnMouseMove(const MouseMoveEvent& evt) {
        if (hidden) {
            return EventResult::UNHANDLED;
        }

        if (IsInside(evt.relPos)) {
            state->hovered = this;
            return EventResult::HANDLED;
        }

        return EventResult::UNHANDLED;
    };
    /// TODO : ... other handlers

public:

    dr4::Texture* GetTexture() const {return texture;};

    Widget(const dr4::Rect2f& rect_, State *state_, Widget *parent_)
        :rect(rect_), parent(parent_), state(state_), texture(state->window->CreateTexture()) {
        texture->SetSize(rect.size);
        texture->SetPos(rect.pos);
    };

    // REVIEW : move implementations to cpp files?

    dr4::Vec2f GetRelPos() const { return rect.pos; };
    virtual void SetRelPos(dr4::Vec2f pos) { rect.pos = pos; };

    dr4::Vec2f GetSize() const { return texture->GetSize(); }
    virtual void SetSize(dr4::Vec2f size) { texture->SetSize(size); rect.size = size; }

    virtual Widget *GetParent() const { return parent; };
    virtual void SetParent(Widget *parent_) { parent = parent_; }
};

}; // namespace hui

#endif // I_HUI_WIDGET
