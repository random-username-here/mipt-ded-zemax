#include <cassert>

#include "hui/container.hpp"
#include "hui/event.hpp"
#include "hui/ui.hpp"

namespace hui {

Container::Container(hui::UI *ui): Widget(ui) {}
Container::~Container() = default;

void Container::BecomeParentOf(Widget *child) {
    assert(child);
    assert(child->GetParent() == nullptr);
    child->SetParent(this);
}

void Container::UnbecomeParentOf(Widget *child) {
    assert(child);
    assert(child->GetParent() == this);
    child->SetParent(nullptr);
}

EventResult Container::OnMouseDown(MouseButtonEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropagateToChildren(evt) == EventResult::HANDLED) {
            evt.pos += GetPos();
            return EventResult::HANDLED;
        } else {
            evt.pos += GetPos();
            return Widget::OnMouseDown(evt);
        }
    }        
    return EventResult::UNHANDLED;
}

EventResult Container::OnMouseUp(MouseButtonEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropagateToChildren(evt) == EventResult::HANDLED) {
            return EventResult::HANDLED;
            evt.pos += GetPos();
        } else {
            evt.pos += GetPos();
            return Widget::OnMouseUp(evt);
        }
    }         
    return EventResult::UNHANDLED;
}

EventResult Container::OnMouseMove(MouseMoveEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropagateToChildren(evt) == EventResult::HANDLED) {
            evt.pos += GetPos();
            return EventResult::HANDLED;
        } else {
            evt.pos += GetPos();
            return Widget::OnMouseMove(evt);
        }
    }
    return EventResult::UNHANDLED;
}

EventResult Container::OnMouseWheel(MouseWheelEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropagateToChildren(evt) == EventResult::HANDLED) {
            evt.pos += GetPos();
            return EventResult::HANDLED;
        } else {
            evt.pos += GetPos();
            return Widget::OnMouseWheel(evt);
        }
    } 
    return EventResult::UNHANDLED;
}

EventResult Container::OnIdle(IdleEvent &evt) {
    PropagateToChildren(evt);
    Widget::OnIdle(evt);
    return EventResult::UNHANDLED;
}

}; // namespace hui
