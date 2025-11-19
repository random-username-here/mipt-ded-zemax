#include <cassert>
#include <iostream>

#include "dr4/math/vec2.hpp"
#include "hui/widget.hpp"
#include "hui/event.hpp"
#include "hui/state.hpp"

namespace hui {

//------------------------------------------------------------------------------
// Management

Widget::Widget(State *state_) :
state(state_), 
rect(0, 0, 0, 0),
texture(state->GetWindow()->CreateTexture()),
extents(0) 
{ }

Widget::~Widget() {
    delete texture;
}

void Widget::SetParent(Widget *parent_) { parent = parent_; }

Widget *Widget::GetParent() const { return parent; }
State  *Widget::GetState()  const { return state; }

//------------------------------------------------------------------------------
// Positioning

void Widget::OnSizeChanged() {}

void Widget::SetSize(dr4::Vec2f size) {
    assert(size.x >= 0);
    assert(size.y >= 0);

    rect.size = size;
    texture->SetSize(
        std::max(0.0f, size.x + extents.left + extents.right),
        std::max(0.0f, size.y + extents.top + extents.bottom)
    );
    texture->SetZero(extents.left, extents.top);
    OnSizeChanged();
}

dr4::Vec2f Widget::GetSize() const { return rect.size; }

void Widget::SetPos(dr4::Vec2f pos) {
    rect.pos = pos;
    texture->SetPos(pos.x - extents.top, pos.y - extents.left);
}

dr4::Vec2f Widget::GetPos() const { return rect.pos; }

void Widget::SetRect(dr4::Rect2f rect_) {
    SetSize(rect_.size);
    SetPos(rect_.pos);
}

dr4::Rect2f Widget::GetRect() const { return rect; }

//------------------------------------------------------------------------------
// Drawing

dr4::Texture &Widget::GetTexture() const { return *texture; }

void Widget::SetTextureExtents(BorderMapped<float> extents_) {
    extents = extents_;
    texture->SetSize(
        std::max(0.0f, rect.size.x + extents.left + extents.right),
        std::max(0.0f, rect.size.y + extents.top + extents.bottom)
    );
    texture->SetZero(extents.left, extents.top);
}

void Widget::Redraw() const {}

void Widget::DrawOn(dr4::Texture &dest) const {
    if (textureWillRedraw) {
        Redraw();
        textureWillRedraw = false;
    }
    dest.Draw(*texture);
}

void Widget::ForceRedraw() {
    for (Widget *tgt = this; tgt && !tgt->textureWillRedraw; tgt = tgt->parent) {
        tgt->textureWillRedraw = true;
    }
}

//------------------------------------------------------------------------------
// Events

void Widget::OnHoverGained() { std::cout << "Widget::OnHoverGained is not implemented\n"; abort();}
void Widget::OnHoverLost()   { std::cout << "Widget::OnHoverLost is not implemented\n";   abort();}
void Widget::OnFocusGained() { std::cout << "Widget::OnFocusGained is not implemented\n"; abort();}
void Widget::OnFocusLost()   { std::cout << "Widget::OnFocusLost is not implemented\n";   abort();}

EventResult Widget::OnMouseDown(MouseButtonEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnMouseUp(MouseButtonEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnMouseWheel(MouseWheelEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnKeyDown(KeyEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnKeyUp(KeyEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnText(TextEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnIdle(IdleEvent &evt) { return EventResult::UNHANDLED; }

EventResult Widget::OnMouseMove(MouseMoveEvent &evt) {
    GetState()->ReportHover(this);
    return EventResult::UNHANDLED;
}


};
