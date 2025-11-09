#ifndef I_HUI_WIDGET
#define I_HUI_WIDGET

#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "hui/event.hpp"

#include <memory>

namespace hui {

class State;

 
 struct WidgetIterator {
    struct Concept {
        virtual ~Concept() = default;
        virtual std::unique_ptr<Concept> clone() const = 0;
        virtual void increment() = 0;
        virtual Widget* deref() const = 0;
        virtual bool equal(const Concept& other) const = 0;
    };

    std::unique_ptr<Concept> p;

    WidgetIterator() = default;
    explicit WidgetIterator(std::unique_ptr<Concept> impl) : p(std::move(impl)) {}
    WidgetIterator(const WidgetIterator& o) : p(o.p ? o.p->clone() : nullptr) {}
    WidgetIterator& operator=(const WidgetIterator& o) { p = o.p ? o.p->clone() : nullptr; return *this; }

    Widget* operator*() const { return p->deref(); }
    WidgetIterator& operator++() { p->increment(); return *this; }
    bool operator==(const WidgetIterator& o) const {
        if (!p || !o.p) return !p && !o.p;
        return p->equal(*o.p);
    }
    bool operator!=(const WidgetIterator& o) const { return !(*this == o); }
};


class Widget {

protected:

    dr4::Vec2f relPos; ///< Relative to parent
    Widget *parent = nullptr;
    State *const state;
    dr4::Texture *const texture;
    bool textureIsInvalid;

    /// Redraws widget's texture
    virtual void Redraw() = 0;

    EventResult OnMouseDown(MouseDownEvent &evt);
    /// TODO : ... other handlers

public:

    Widget(State *const state);
    Widget(const std::size_t width, const std::size_t height, 
           State *state, Widget *parent);

    // REVIEW : move implementations to cpp files?
     
 struct WgtIterImlp : WidgetIterator::Concept {
        Widget *widget;
        explicit WgtIterImlp(Widget *): widget(widget) {}
    
        std::unique_ptr<Concept> clone() const override {
            return std::make_unique<WgtIterImlp>(widget);
        }
    
        void increment() override {}

        Widget* deref() const override {
            return widget;
        }
    
        bool equal(const Concept& other) const override {
            if (auto p = dynamic_cast<const WgtIterImlp*>(&other))
                return p->widget == widget;
            return false;
        }
    };

    virtual WidgetIterator begin() { return WidgetIterator(std::make_unique<WgtIterImlp>(this)); }
    virtual WidgetIterator end() { return WidgetIterator(std::make_unique<WgtIterImlp>(nullptr)); }

    dr4::Vec2f GetRelPos() const { return relPos; };
    virtual void SetRelPos(dr4::Vec2f pos) { relPos = pos; };

    dr4::Vec2f GetSize() const { return texture->GetSize(); }
    virtual void SetSize(dr4::Vec2f size) { texture->SetSize(size); }

    virtual Widget *GetParent() const { return parent; };
    virtual void SetParent(Widget *parent_) { parent = parent_; }
};

}; // namespace hui

#endif // I_HUI_WIDGET
