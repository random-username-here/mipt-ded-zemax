#ifndef I_HUI_UI
#define I_HUI_UI
#include <memory>
#include "dr4/window.hpp"
#include "hui/widget.hpp"

namespace hui {

class UI {
    dr4::Window *window  = nullptr;

    hui::Widget *focused       = nullptr;
    hui::Widget *hovered       = nullptr;
    hui::Widget *captured      = nullptr;

    std::unique_ptr<hui::Widget> root;
    dr4::Vec2f pos{};

public:
    UI(dr4::Window *window_);
    ~UI();

    void ProcessEvent(dr4::Event &dr4Event);

    void SetRoot(hui::Widget *widget);
    void SetCaptured(hui::Widget *widget);

    void OnIdle(hui::IdleEvent &evt);

    void ReportHover(Widget *w);
    void ReportFocus(Widget *w);

    dr4::Texture *GetTexture();
    dr4::Window  *GetWindow();
    hui::Widget  *GetFocused();
    hui::Widget  *GetHovered();
    hui::Widget  *GetCaptured();
    hui::Widget  *GetRoot();
    const dr4::Window  *GetWindow()  const;
    const hui::Widget  *GetFocused() const;
    const hui::Widget  *GetHovered() const;
    const hui::Widget  *GetCaptured() const;
    const hui::Widget  *GetRoot()    const;
};

}; // namespace hui

#endif // I_HUI_UI
