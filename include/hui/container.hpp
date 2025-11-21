#ifndef I_HUI_CONTAINER
#define I_HUI_CONTAINER

#include "hui/event.hpp"
#include "hui/widget.hpp"

namespace hui {

/**
 * @brief A widget which contains child widgets
 *
 * This class can become/unbecome parent of other widgets.
 * Being parent of given widget means that widget has it's
 * GetParent() returning the container. Child's memory is NOT
 * MADE MANAGED by the container. 
 *
 * Also this class sends only mouse and idle events down the tree.
 * Mouse events sent down are the ones where pointer is inside
 * widget's rectangle (not texture, which can extend outside!).
 * To implement out-of-bounds chilren a modal widget mechanism
 * will be implemented (or is implemented, but someone forgot to
 * change this comment).
 *
 * Keyboard and input events do not propogate down the tree.
 * If we focus on window to move it with arrow keys, we don't
 * want to input something into it's text fields.
 *
 * Hotkeys should not be implemented using this. They are to
 * be done separately from widget focusing.
 *
 * To override some event handler, you should call this
 * class'es methods to give events to children. Do not
 * implement event propogation to children in OnMouseMove() or
 * other methods like that yourself.
 *
 */
class Container : public Widget {

public:
    Container(hui::UI *ui);
    virtual ~Container();

protected:
    void BecomeParentOf(Widget *child);
    void UnbecomeParentOf(Widget *child);

    virtual EventResult PropagateToChildren(Event &event) = 0;

    // All those send the event to all children
    EventResult OnMouseDown(MouseButtonEvent &evt) override;
    EventResult OnMouseUp(MouseButtonEvent &evt) override;
    EventResult OnMouseMove(MouseMoveEvent &evt) override;
    EventResult OnMouseWheel(MouseWheelEvent &evt) override;
    EventResult OnIdle(IdleEvent &evt) override;
};

}; // namespace hui

#endif // I_HUI_CONTAINER
