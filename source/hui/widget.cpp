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

Widget::~Widget() = default;

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
    OnSizeChanged();
}

dr4::Vec2f Widget::GetSize() const { return rect.size; }

void Widget::SetPos(dr4::Vec2f pos) { // FIXME
    rect.pos = pos;
    texture->SetPos(pos.x - extents.left, pos.y - extents.top);
}

dr4::Vec2f Widget::GetPos() const { return rect.pos; }

void Widget::SetRect(dr4::Rect2f rect_) {
    SetSize(rect_.size);
    SetPos(rect_.pos);
}

dr4::Rect2f Widget::GetRect() const { return rect; }

dr4::Vec2f Widget::GetAbsolutePos() const {
    dr4::Vec2f pos = GetPos();
    if (auto p = GetParent()) pos += p->GetAbsolutePos();
    return pos;
}

const BorderMapped<float> &Widget::GetTextureExtents() const {
    return extents;
}

dr4::Texture &Widget::GetFreshTexture() {
    if (textureWillRedraw) {
        Redraw();
        textureWillRedraw = false;
    }
    return GetTexture();
}

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

EventResult Widget::OnMouseDown  (MouseButtonEvent &evt) { 
    if (!GetRect().Contains(evt.pos)) return EventResult::UNHANDLED; 
    GetUI()->ReportFocus(this);
    return EventResult::UNHANDLED; 
}

EventResult Widget::OnMouseUp    (MouseButtonEvent &) { return EventResult::UNHANDLED; }
EventResult Widget::OnMouseWheel (MouseWheelEvent &)  { return EventResult::UNHANDLED; }
EventResult Widget::OnKeyUp      (KeyEvent &)         { return EventResult::UNHANDLED; }
EventResult Widget::OnText       (TextEvent &)        { return EventResult::UNHANDLED; }
EventResult Widget::OnIdle       (IdleEvent &)        { return EventResult::UNHANDLED; }

EventResult Widget::OnMouseMove (MouseMoveEvent &evt) {
    if (!GetRect().Contains(evt.pos)) return EventResult::UNHANDLED; 
    GetUI()->ReportHover(this);
    return EventResult::HANDLED;
}

EventResult Widget::OnKeyDown(KeyEvent &) { 
    return EventResult::UNHANDLED; 
}

}; // namespace hui
