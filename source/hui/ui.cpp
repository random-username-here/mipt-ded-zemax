#include <iostream>

#include "hui/ui.hpp"
#include "cassert"

namespace hui {

UI::UI(dr4::Window *window_): window(window_) {}
UI::~UI() = default;

void UI::ProcessEvent(dr4::Event &dr4Event) {
    switch (dr4Event.type) {
        case dr4::Event::Type::KEY_DOWN:
            {
                hui::KeyEvent keyEvent = {};
                keyEvent.key = dr4Event.key.sym;
                keyEvent.mods = dr4Event.key.mods;
                keyEvent.pressed = true;

                if (focused) { keyEvent.Apply(*focused); break; }
                if (root) keyEvent.Apply(*root);
                break;
            } 
        case dr4::Event::Type::KEY_UP:
            {
                hui::KeyEvent keyEvent = {};
                keyEvent.key = dr4Event.key.sym;
                keyEvent.mods = dr4Event.key.mods;
                keyEvent.pressed = false;

                if (focused) { keyEvent.Apply(*focused); }
                if (root) keyEvent.Apply(*root);
                break;
            }
        case dr4::Event::Type::MOUSE_MOVE:
            {
                hui::MouseMoveEvent mouseMoveEvent = {};
                mouseMoveEvent.rel = dr4Event.mouseMove.rel;
                mouseMoveEvent.pos = dr4Event.mouseMove.pos;
            
                if (captured) {
                    if (captured->GetParent())
                        mouseMoveEvent.pos -= captured->GetParent()->GetAbsolutePos();
                    mouseMoveEvent.Apply(*captured);
                    break;
                }

                hui::Widget *prevHovered = hovered;
                hovered = nullptr;

                if (root) mouseMoveEvent.Apply(*root);

                if (prevHovered == hovered) break;
                if (prevHovered) {
                    prevHovered->OnHoverLost();
                }
                
                if (hovered) hovered->OnHoverGained(); 
                break;
            }
        case dr4::Event::Type::MOUSE_DOWN:
            {
                hui::MouseButtonEvent mouseDownEvent = {};
                mouseDownEvent.button = dr4Event.mouseButton.button;
                mouseDownEvent.pressed = true;
                mouseDownEvent.pos = dr4Event.mouseButton.pos;

                if (captured) {
                    if (captured->GetParent())
                        mouseDownEvent.pos -= captured->GetParent()->GetAbsolutePos();
                    mouseDownEvent.Apply(*captured);
                    break;
                }

                hui::Widget *prevFocused = focused;
                focused = nullptr;

                if (root) mouseDownEvent.Apply(*root);

                if (prevFocused == focused) break;
                if (prevFocused) prevFocused->OnFocusLost();
                if (focused) focused->OnFocusGained();
                break;
            }
        case dr4::Event::Type::MOUSE_UP:
            {
                hui::MouseButtonEvent mouseUpEvent = {};
                mouseUpEvent.button = dr4Event.mouseButton.button;
                mouseUpEvent.pressed = false;
                mouseUpEvent.pos = dr4Event.mouseButton.pos;

                if (captured) {
                    if (captured->GetParent())
                        mouseUpEvent.pos -= captured->GetParent()->GetAbsolutePos();
                    mouseUpEvent.Apply(*captured);
                    break;
                }

                if (root) mouseUpEvent.Apply(*root);
                break;
            }
        case dr4::Event::Type::MOUSE_WHEEL:
            {
                hui::MouseWheelEvent mouseWheelEvent = {};
                mouseWheelEvent.delta = dr4Event.mouseWheel.delta;
                mouseWheelEvent.pos = dr4Event.mouseWheel.pos;

                if (captured) {
                    if (captured->GetParent())
                        mouseWheelEvent.pos -= captured->GetParent()->GetAbsolutePos();
                    mouseWheelEvent.Apply(*captured);
                    break;
                }

                if (root) mouseWheelEvent.Apply(*root);
                break;
            }
        case dr4::Event::Type::TEXT_EVENT:
            {
                hui::TextEvent textEvent = {};
                textEvent.text = dr4Event.text.unicode;

                if (focused) { textEvent.Apply(*focused); }
                if (root) textEvent.Apply(*root);
                break;
            }
        case dr4::Event::Type::QUIT: break;
        default:
            std::cerr << "unknown event : " << static_cast<int>(dr4Event.type) << "\n";
    }
}

void UI::DrawOn(dr4::Texture& dstTexture_) const { 
    if (root)
        root->DrawOn(dstTexture_);
}

void UI::SetPos(dr4::Vec2f pos_) { 
    if (root) root->SetPos(pos_);
}


dr4::Vec2f UI::GetPos() const {
    if (root) return root->GetPos();
    return {0.0, 0.0};
}

void UI::SetRoot(hui::Widget *widget) { 
    root.reset(widget); 
}

void UI::SetCaptured(hui::Widget *widget) {
    captured = widget;
}

void UI::OnIdle(hui::IdleEvent &evt) { if (root) evt.Apply(*root); }

void UI::ReportHover(Widget *w) { if (!hovered) hovered = w; }
void UI::ReportFocus(Widget *w) { if (!focused) focused = w; } 

dr4::Texture *UI::GetTexture() { 
    if (!root) return nullptr;
    
    return &root->GetFreshTexture();
}

const dr4::Window  *UI::GetWindow()  const { return window; } 
const hui::Widget  *UI::GetFocused() const { return focused; }
const hui::Widget  *UI::GetHovered() const { return hovered; }
const hui::Widget  *UI::GetRoot()    const { return root.get();}

dr4::Window  *UI::GetWindow()  { return window; } 
hui::Widget  *UI::GetFocused() { return focused; }
hui::Widget  *UI::GetHovered() { return hovered; }
hui::Widget  *UI::GetRoot()    { return root.get();}

}; // namespace hui
