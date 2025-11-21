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

                if (focused) { keyEvent.Apply(*focused); }
                break;
            } 
        case dr4::Event::Type::KEY_UP:
            {
                hui::KeyEvent keyEvent = {};
                keyEvent.key = dr4Event.key.sym;
                keyEvent.mods = dr4Event.key.mods;
                keyEvent.pressed = false;

                if (focused) { keyEvent.Apply(*focused); }
                break;
            }
        case dr4::Event::Type::MOUSE_MOVE:
            {
                hui::MouseMoveEvent mouseMoveEvent = {};
                mouseMoveEvent.rel = dr4Event.mouseMove.rel;
                mouseMoveEvent.pos = dr4Event.mouseMove.pos;

                hui::Widget *prevHovered = hovered;
                hovered = nullptr;
                
                if (root) { 
                    if (root->GetRect().Contains(mouseMoveEvent.pos)) {
                        mouseMoveEvent.Apply(*root); 
                    }
                }

                if (prevHovered == hovered) break;
                if (prevHovered) prevHovered->OnHoverLost();
                if (hovered) hovered->OnHoverGained(); 
                break;
            }
        case dr4::Event::Type::MOUSE_DOWN:
            {
                hui::MouseButtonEvent mouseDownEvent = {};
                mouseDownEvent.button = dr4Event.mouseButton.button;
                mouseDownEvent.pressed = true;
                mouseDownEvent.pos = dr4Event.mouseButton.pos;

                hui::Widget *prevFocused = focused;
                focused = nullptr;
                
                if (root) {     
                    if (root->GetRect().Contains(mouseDownEvent.pos))
                        mouseDownEvent.Apply(*root); 
                }

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
                if (root) { 
                    if (root->GetRect().Contains(mouseUpEvent.pos))
                        mouseUpEvent.Apply(*root); 
                }
                break;
            }
        case dr4::Event::Type::MOUSE_WHEEL:
            {
                hui::MouseWheelEvent mouseWheelEvent = {};
                mouseWheelEvent.delta = dr4::Vec2f(dr4Event.mouseWheel.deltaX, dr4Event.mouseWheel.deltaY);
                mouseWheelEvent.pos = dr4Event.mouseWheel.pos;

                if (focused) { 
                    if (focused->GetParent() != nullptr)
                        mouseWheelEvent.pos -= focused->GetParent()->GetAbsolutePos();
                    if (focused->GetRect().Contains(mouseWheelEvent.pos))
                        mouseWheelEvent.Apply(*focused); 
                }
                break;
            }
        case dr4::Event::Type::TEXT_EVENT:
            {
                hui::TextEvent textEvent = {};
                textEvent.text = dr4Event.text.unicode;

                if (focused) { textEvent.Apply(*focused); }
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

void UI::SetPos(dr4::Vec2f pos_) { pos = pos_; }
dr4::Vec2f UI::GetPos() const { return pos; }

void UI::SetRoot(hui::Widget *widget) { 
    root = widget; 
}

void UI::OnIdle(hui::IdleEvent &evt) { if (root) evt.Apply(*root); }

void UI::ReportHover(Widget *w) { if (!hovered) hovered = w; }
void UI::ReportFocus(Widget *w) { if (!focused) focused = w; } 

dr4::Texture *UI::GetTexture() const { 
    if (!root) return nullptr;
    
    return &root->GetFreshTexture();
}

dr4::Window  *UI::GetWindow()  const { return window; } 
hui::Widget  *UI::GetFocused() const { return focused; }
hui::Widget  *UI::GetHovered() const { return hovered; }
hui::Widget  *UI::GetRoot()    const { return root;}

}; // namespace hui