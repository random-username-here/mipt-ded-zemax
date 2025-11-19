#include "hui/container.hpp"
#include "hui/event.hpp"
#include <cassert>

namespace hui {

void Container::BecomeParentOf(Widget *child) {
    assert(child->GetParent() == nullptr);
    child->SetParent(this);
}

void Container::UnbecomeParentOf(Widget *child) {
    assert(child->GetParent() == this);
    child->SetParent(nullptr);
}

EventResult Container::OnMouseDown(MouseButtonEvent &evt) {
    if (GetRect().Contains(evt.relPos) && PropogateToChildren(evt) == EventResult::HANDLED)
        return EventResult::HANDLED;
    else
        return Widget::OnMouseDown(evt);
}
EventResult Container::OnMouseUp(MouseButtonEvent &evt) {
    if (GetRect().Contains(evt.relPos) && PropogateToChildren(evt) == EventResult::HANDLED)
        return EventResult::HANDLED;
    else
        return Widget::OnMouseUp(evt);
   
}
EventResult Container::OnMouseMove(MouseMoveEvent &evt) {
    if (GetRect().Contains(evt.relPos) && PropogateToChildren(evt) == EventResult::HANDLED)
        return EventResult::HANDLED;
    else
        return Widget::OnMouseMove(evt);
}
EventResult Container::OnMouseWheel(MouseWheelEvent &evt) {
    if (GetRect().Contains(evt.relPos) && PropogateToChildren(evt) == EventResult::HANDLED)
        return EventResult::HANDLED;
    else
        return Widget::OnMouseWheel(evt);   
}

EventResult Container::OnIdle(IdleEvent &evt) {
    PropogateToChildren(evt);
    Widget::OnIdle(evt);
    return EventResult::HANDLED;
}





};
