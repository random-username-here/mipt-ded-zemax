#include <cassert>
#include <iostream>

#include "dr4/math/vec2.hpp"
#include "hui/widget.hpp"
#include "hui/event.hpp"
#include "hui/ui.hpp"

namespace hui {

//------------------------------------------------------------------------------
// Management

Widget::Widget(UI *ui_) :
    ui(ui_), 
    rect(0, 0, 0, 0),
    texture(ui_->GetWindow()->CreateTexture()),
    extents(0) {}

Widget::~Widget() {
    delete texture;
}

void Widget::SetParent(Widget *parent_) { parent = parent_; }

Widget *Widget::GetParent() const { return parent; }
UI  *Widget::GetUI() const { return ui; }

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

void Widget::OnHoverGained() { return; }
void Widget::OnHoverLost()   { return; }
void Widget::OnFocusGained() { return; }
void Widget::OnFocusLost()   { return; }

EventResult Widget::OnMouseDown  ([[maybe_unused]] MouseButtonEvent &evt) { 
    GetUI()->ReportFocus(this);
    return EventResult::UNHANDLED; 
}
EventResult Widget::OnMouseUp    ([[maybe_unused]] MouseButtonEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnMouseWheel ([[maybe_unused]] MouseWheelEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnKeyDown    ([[maybe_unused]] KeyEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnKeyUp      ([[maybe_unused]] KeyEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnText       ([[maybe_unused]] TextEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnIdle       ([[maybe_unused]] IdleEvent &evt) { return EventResult::UNHANDLED; }
EventResult Widget::OnMouseMove  ([[maybe_unused]] MouseMoveEvent &evt) {
    GetUI()->ReportHover(this);
    return EventResult::UNHANDLED;
}

}; // namespace hui
