#ifndef I_HUI_WIDGET
#define I_HUI_WIDGET

#include <memory>
#include <cassert>

#include "dr4/math/vec2.hpp"
#include "dr4/mouse_buttons.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "hui/event.hpp"

namespace hui {

class Widget;

struct State {
    const hui::Widget* hoveredWidget;
    const hui::Widget* focusedWidget;

    dr4::Window* window;
};

// TODO handle exceptions

class Widget: public dr4::Drawable {

public:

    Widget(dr4::Vec2f size)
        :   state_{nullptr},
            texture_(state_->window->CreateTexture()),
            rect_{state_->window->CreateRectangle()},
            parent_{nullptr},
            textureIsInvalid_{true}
    {
        texture_->SetSize(size);

        rect_->SetSize(size);
    }

    
    virtual void SetPos(dr4::Vec2f pos) override { 
        texture_->SetPos(pos);
    };
    virtual dr4::Vec2f GetPos() const override { 
        return texture_->GetPos();
    };
    virtual void DrawOn(dr4::Texture& srcTexture) const override {
        if (isHide_) return;

        if (textureIsInvalid_) {
            Redraw();
        }

        texture_->DrawOn(srcTexture);
    }

    virtual void SetTextureIsInvalid() {
        textureIsInvalid_ = true;
        if (parent_) {
            parent_->SetTextureIsInvalid();
        }
    }
    virtual void SetParent(Widget *parent) { 
        parent_ = parent; 
    }
    virtual void SetFillColor(dr4::Color color) {
        rect_->SetFillColor(color);
        SetTextureIsInvalid();
    }
    virtual void SetBorderThickness(float thickness) {
        rect_->SetBorderThickness(thickness);
        SetTextureIsInvalid();
    }
    virtual void SetBorderColor(dr4::Color color) {
        rect_->SetBorderColor(color);
        SetTextureIsInvalid();
    }
    virtual void SetIsFocusable(bool isFocusable) {
        isFocusable_ = isFocusable;
    }
    virtual void SetFocusButton(dr4::MouseButtonType focusButton) {
        focusButton_ = focusButton;
    }
    virtual void SetIsHide(bool isHide) {
        isHide_ = true;
        SetTextureIsInvalid();
    }
    virtual void SetMusRemoved(bool mustRemoved) {
        mustRemoved_ = true;
        SetTextureIsInvalid();
    }
    virtual void SetState(State& state) {
        state_ = &state;
    }

    const dr4::Rectangle& GetRect() const noexcept {
        assert(rect_);
        return *rect_;
    }
    const State& GetState() const noexcept {
        assert(state_);
        return *state_;
    }
    const Widget* GetParent() const noexcept {
        return parent_;
    }
    bool GetTextureIsInvalid() const noexcept {
        return textureIsInvalid_;
    }
    bool GetIsFocusable() const noexcept {
        return isFocusable_;
    }
    dr4::MouseButtonType GetFocusButton() const noexcept {
        return focusButton_;
    }
    bool GetIsHide() const noexcept {
        return isHide_;
    }
    bool GetMustRemoved() const noexcept {
        return mustRemoved_;
    }

protected:

    virtual void Redraw() const {
        rect_->DrawOn(*texture_);
    }

protected:

    State * state_;

    std::unique_ptr<dr4::Texture> texture_;
    std::unique_ptr<dr4::Rectangle> rect_;

    Widget *parent_;
    bool textureIsInvalid_;

    bool isFocusable_;
    dr4::MouseButtonType focusButton_;


    bool isHide_;
    bool mustRemoved_;

};



}; // namespace hui

#endif // I_HUI_WIDGET
