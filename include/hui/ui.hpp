#ifndef I_HUI_UI
#define I_HUI_UI

#include "hui/hui_except.hpp"
#include "dr4/window.hpp"
#include "hui/widget.hpp"

namespace hui {

class UI : public dr4::Drawable {
    dr4::Window *window = nullptr;

    hui::Widget *focused = nullptr;
    hui::Widget *hovered = nullptr;
    hui::Widget *root    = nullptr;
    dr4::Vec2f pos{};

public:
    UI(dr4::Window *window_);
    ~UI();

    void ProcessEvent(dr4::Event &dr4Event);
    void DrawOn(dr4::Texture& dstTexture_) const override;

    void SetPos(dr4::Vec2f pos) override;
    dr4::Vec2f GetPos() const override;

    void SetRoot(hui::Widget *widget);

    void OnIdle(hui::IdleEvent &evt);

    void ReportHover(Widget *w);
    void ReportFocus(Widget *w);

    dr4::Texture *GetTexture() const;
    dr4::Window  *GetWindow()  const;
    hui::Widget  *GetFocused() const;
    hui::Widget  *GetHovered() const;
    hui::Widget  *GetRoot()    const;
};

}; // namespace hui

#endif // I_HUI_UI
