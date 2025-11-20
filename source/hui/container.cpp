#include <cassert>

#include "hui/container.hpp"
#include "hui/event.hpp"
#include "hui/ui.hpp"
#include <iostream>

namespace hui {

Container::Container(hui::UI *ui): Widget(ui) {}
Container::~Container() {};

void Container::BecomeParentOf(Widget *child) {
    assert(child->GetParent() == nullptr);
    child->SetParent(this);
}

void Container::UnbecomeParentOf(Widget *child) {
    assert(child->GetParent() == this);
    child->SetParent(nullptr);
}

EventResult Container::OnMouseDown(MouseButtonEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropogateToChildren(evt) == EventResult::HANDLED)
            return EventResult::HANDLED;
        else
            return Widget::OnMouseDown(evt);
    }        
    return EventResult::UNHANDLED;
}

EventResult Container::OnMouseUp(MouseButtonEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropogateToChildren(evt) == EventResult::HANDLED)
            return EventResult::HANDLED;
        else
            return Widget::OnMouseUp(evt);
    }         
    return EventResult::UNHANDLED;
}

EventResult Container::OnMouseMove(MouseMoveEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropogateToChildren(evt) == EventResult::HANDLED)
            return EventResult::HANDLED;
        else
            return Widget::OnMouseMove(evt);
    }
    return EventResult::UNHANDLED;
}

EventResult Container::OnMouseWheel(MouseWheelEvent &evt) {
    if (GetRect().Contains(evt.pos)) {
        evt.pos -= GetPos();
        if (PropogateToChildren(evt) == EventResult::HANDLED)
            return EventResult::HANDLED;
        else
            return Widget::OnMouseWheel(evt);
    } 
    return EventResult::UNHANDLED;
}

EventResult Container::OnIdle(IdleEvent &evt) {
    PropogateToChildren(evt);
    Widget::OnIdle(evt);
    return EventResult::HANDLED;
}

}; // namespace hui