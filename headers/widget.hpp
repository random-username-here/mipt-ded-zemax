#pragma once
/**
 * @file
 * @brief Minimal event/dispatch framework for widgets.
 *
 * This header defines a small hierarchy of UI events and a co-operative
 * dispatch mechanism shared by **Widget** and its derived types.
 *
 * Key ideas:
 * - **DispatcherCtx** carries per-dispatch state (mouse coordinates, clipping
 * viewport, and the target window). Handlers may derive child contexts with
 * local offsets and tighter clipping.
 * - **Event** is an abstract base for concrete events (render, layout, input,
 * idle, quit). Each event knows how to deliver itself to a widget.
 * - **DispatchResult** indicates whether an event was consumed or should
 * continue propagating.
 * - **Widget** is the base UI node. It provides default handlers that usually
 * propagate, and utilities for layout, hit-testing and rendering.
 * - **ControlledWidget / Control** allow composing a widget with a set of
 * attached controller-like children that participate in dispatch.
 * - **ScrollableWidget** extends **Widget** with an independent viewport for
 * scrollable content.
 *
 * Coordinates & clipping:
 * - `DispatcherCtx::mouseAbs` is in window/screen coordinates.
 * - `DispatcherCtx::mouseRel` is relative to the current widget's local
 * origin (top-left of its frame).
 * - `DispatcherCtx::viewport` is a clip rectangle in the *current* local space
 * that constrains drawing and hit-tests.
 *
 * Threading: this API is **not** thread-safe. All interactions are expected
 * to occur on the UI/main thread that owns the Window.
 */

#include <cstdint>
#include <vector>

/**
 * @brief 2D point in UI coordinate space.
 *
 * Conventions:
 * - Units: pixels.
 * - Coordinate system: origin at the top-left; +X to the right, +Y down.
 * - Values are finite floats; no special semantics for NaN/Inf.
 */
struct Vec2F {
    float x, y;
};

/**
 * @brief Axis-aligned rectangle in UI coordinate space.
 *
 * Semantics:
 * - (x, y) is the top-left corner; (w, h) are width/height in pixels.
 * - Invariants: w >= 0, h >= 0.
 * - Edge convention: half-open interval [x, x + w) x [y, y + h)
 *
 * Notes:
 * - Interacts with clipping/hit-testing (see DispatcherCtx::viewport and
 *   intersect()).
 * - Rects are expressed in the local space of their owner unless stated otherwise.
 */
struct Rect2F {
    float x, y, w, h;
};

/**
 * @brief Time in seconds (double precision).
 *
 * Used for deltas (e.g., IdleEvent::dt), budgets, and absolute deadlines.
 * Assumed to be monotonic when used as a timestamp source.
 */
typedef double Time;

// forward-declare
class Widget;
class Window;
struct State;

/**
 * @brief Per-dispatch context shared across event delivery.
 *
 * A context flows down the widget tree so handlers can compute relative
 * positions and clip regions. Handlers should treat this as immutable and
 * create derived contexts when adjusting offsets/clipping.
 */
struct DispatcherCtx {
    /** Mouse position in the current widget's local space. */
    Vec2F  mouseRel;
    /** Mouse position in absolute coordinates. */
    Vec2F  mouseAbs;
    /** Active clip rectangle in the current local space. */
    Rect2F viewport;
    /** Target window for rendering. May be null for non-render events. */
    Window *window;

    /**
     * @brief Intersect the current viewport with @p frame.
     */
    void clip(Rect2F frame);

    /**
     * @return Offset to transform local coordinates to absolute ones, i.e.
     * `abs = rel + offset()`.
     */
    Vec2F offset();

    /**
     * @brief Create a child context translated by @p frame's top-left.
     *
     * Useful when descending into a child whose frame is expressed relative to
     * the current widget.
     */
    DispatcherCtx withOffset(Rect2F frame) const;

    /**
     * @brief Build a root context from absolute mouse and initial clip.
     * @param abs Mouse position in absolute coordinates.
     * @param clip Initial clip rectangle in root-local coordinates.
     * @param window Window to render into (may be null during layout).
     */
    static DispatcherCtx fromAbsolute(Vec2F abs, Rect2F clip, Window *window);
};

/**
 * @brief Result of dispatch.
 * - PROPAGATE:	event was not consumed; continue propagation.
 * - CONSUME:	event handled; stop propagation.
 */
enum DispatchResult { PROPAGATE, CONSUME };

/**
 * @brief Abstract base for all events.
 *
 * Every event implements `deliver(ctx, widget)` to invoke the appropriate
 * handler on @p widget.
 */
struct Event {
    virtual ~Event();
    virtual DispatchResult deliver(DispatcherCtx, Widget *) = 0;
};

/** @brief Rendering pass (draw the widget). */
struct RenderEvent : Event {
    DispatchResult deliver(DispatcherCtx, Widget *);
};

/** @brief Layout pass (arrange children, update frames). */
struct LayoutEvent : Event {
    DispatchResult deliver(DispatcherCtx, Widget *);
};

/**
 * @brief Idle time slice for background work/animations.
 * @param dt Time elapsed since last idle tick (seconds).
 * @param budget Recommended maximum processing time (seconds).
 * @param deadline Absolute deadline timestamp (seconds).
 */
struct IdleEvent : public Event {
    Time dt;
    Time budget;
    Time deadline;
    IdleEvent(Time dt_, Time budget_, Time deadline_);

    DispatchResult deliver(DispatcherCtx, Widget *);
};

/** @brief Request to close the application/window. */
struct QuitRequestEvent : Event {
    DispatchResult deliver(DispatcherCtx, Widget *);
};

/** @brief Mouse moved. */
struct MouseMoveEvent : Event {
    Vec2F mouseAbs;
    MouseMoveEvent(Vec2F mouseAbs_);

    DispatchResult deliver(DispatcherCtx, Widget *);
};

/** @brief Mouse button pressed. */
struct MouseDownEvent : Event {
    Vec2F mouseAbs;
    MouseDownEvent(Vec2F mouseAbs_) : mouseAbs(mouseAbs_) {}

    DispatchResult deliver(DispatcherCtx, Widget *);
};

/** @brief Mouse button released. */
struct MouseUpEvent : Event {
    MouseUpEvent() {}

    DispatchResult deliver(DispatcherCtx, Widget *);
};

/**
 * @brief Base keyboard event.
 * @note `scancode` is platform-neutral; `keycode` and `mods` are translated
 * from the platform layer. `mods` is a bitmask (e.g., Ctrl/Alt/Shift).
 */
struct KeyEvent : Event {
    int scancode;   //!< Platform-neutral scan code.
    int keycode;    //!< Logical key code.
    uint16_t mods;  //!< Modifier bitmask.

    KeyEvent(int scancode_, int keycode_, uint32_t mods_);
};

/** @brief Key down. */
struct KeyDownEvent : KeyEvent {
    bool repeat;  //!< True if generated by key auto-repeat.
    KeyDownEvent(int scancode_, int keycode_, uint32_t mods_, bool repeat_);

    DispatchResult deliver(DispatcherCtx, Widget *);
};

/** @brief Key released. */
struct KeyUpEvent : KeyEvent {
    KeyUpEvent(int scancode_, int keycode_, uint32_t mods_);

    DispatchResult deliver(DispatcherCtx, Widget *);
};

// forward-declare
class Surface;

/**
 * @brief Base class for all UI elements.
 *
 * Widgets form a tree via their `parent` pointer. A widget's `frame` is
 * expressed relative to its parent.
 */
class Widget {
private:
    State   *state_;        //!< Shared UI state.
    Surface *surface_;      //!< Rendering surface.
    bool     needsRedraw_;  //!< Whether a widget changed visually.

protected:
    Widget *parent_;  //!< Parent widget.
    Rect2F  frame_;   //!< Local frame; `x` and `y` are relative to `parent`.

public:
    Widget(Rect2F frame, Widget *parent, State *state) {}
    virtual ~Widget();

    /** @return Short, human-readable name used for tooling/debugging. */
    virtual const char *title() const = 0;

    /** @return The current viewport used for clipping/hit-testing. */
    virtual Rect2F getViewport() const;

    /** @brief Get the widget's frame. */
    virtual Rect2F getFrame();
    /** @brief Update the widget's frame. */
    virtual void   setFrame(Rect2F newFrame);

    /** @brief Get the widget's parent. */
    virtual Widget *getParent();
    /** @brief Update the widget's parent. */
    virtual void    setParent(Widget *parent);

    /**
     * @brief Basic hit-test against current viewport in local space.
     * @return True if `ctx.mouseRel` lies within `ctx.viewport`.
     */
    virtual bool containsMouse(DispatcherCtx ctx) const;

    /** @brief Draw the widget to a surface. */
    virtual void draw() = 0;

    const Surface *requestSurface();

    void requestRedraw();

    // Input & lifecycle hooks (default: PROPAGATE)
    virtual DispatchResult onMouseMove  (DispatcherCtx, const MouseMoveEvent   &);
    virtual DispatchResult onMouseDown  (DispatcherCtx, const MouseDownEvent   &);
    virtual DispatchResult onMouseUp    (DispatcherCtx, const MouseUpEvent     &);
    virtual DispatchResult onKeyDown    (DispatcherCtx, const KeyDownEvent     &);
    virtual DispatchResult onKeyUp      (DispatcherCtx, const KeyUpEvent       &);
    virtual DispatchResult onIdle        (DispatcherCtx, const IdleEvent        &);
    virtual DispatchResult onQuitRequest(DispatcherCtx, const QuitRequestEvent &);
    virtual DispatchResult onLayout      (DispatcherCtx, const LayoutEvent      &);

    /**
     * @brief Deliver @p e to this widget (and optionally children).
     */
    virtual DispatchResult broadcast(DispatcherCtx ctx, Event *e);

    /**
     * @brief Request a synchronous layout pass starting at this widget.
     */
    void refreshLayout();

    /**
     * @brief Compose a context that is correct for this widget as the root of a
     * dispatch (e.g., starting a layout pass from here).
     */
    DispatcherCtx resolveContext(Window *) const;
};

/**
 * @brief Generic container that owns a list of child widgets and forwards event dispatch to them.
 */
class WidgetContainer : public virtual Widget {
protected:
    /** Child widgets in dispatch order. */
    std::vector<Widget*> children_;

public:
    WidgetContainer(Rect2F, Widget *, State *);
    /** Construct a container pre-populated with @p children. */
    WidgetContainer(Rect2F, Widget *, std::vector<Widget*> children, State *);

    /**
     * @brief Append a child and adopt it (set its `parent` to `this`).
     * @note Transfers ownership.
     */
    void appendChild(Widget*);

    /**
     * @brief Dispatch to children, then this widget.
     */
    DispatchResult broadcast(DispatcherCtx ctx, Event *e);
};

/**
 * @brief Widget that supports click-and-drag repositioning.
 *
 * This class provides a basic interaction pattern: press to begin dragging,
 * move to update position, release to stop. Exact movement rules depend on the
 * implementation of the handlers, but the typical behavior is to translate the
 * widget's frame within its parent coordinate space.
 */
class DraggableWidget : public virtual Widget {
protected:
    /** Position of the widget's parent-space origin at drag start. */
    Vec2F startDrag_;
    /** True while a drag interaction is active. */
    bool isDragging_;

public:
    DraggableWidget(Rect2F, Widget *, State *);

    /**
     * @brief Pointer moved; update position if a drag is active.
     */
    DispatchResult onMouseMove(DispatcherCtx, const MouseMoveEvent &);

    /**
     * @brief Begin dragging when the pointer is pressed inside this widget.
     */
    DispatchResult onMouseDown(DispatcherCtx, const MouseDownEvent &);

    /**
     * @brief End a drag interaction.
     */
    DispatchResult onMouseUp  (DispatcherCtx, const MouseUpEvent   &);
};

class ControlledWidget;  // forward-declare

/**
 * @brief Controller that can attach to a ControlledWidget host.
 *
 * Controls are auxiliary widgets that receive events through their host and
 * can influence behavior (e.g., titlebars, scrollbars).
 */
class Control : public virtual Widget {
public:
    Control(Rect2F, Widget *, State *);

    /** Attach this control to a host widget. */
    virtual void attachTo(ControlledWidget *host) = 0;
};

/**
 * @brief Widget that manages a list of attached `Control` children.
 */
class ControlledWidget : public virtual Widget {
protected:
    std::vector<Control*> controls;

public:
    ControlledWidget(Rect2F, Widget *, State *);

    /**
     * @brief Attach a control and adopt it as a child.
     * @note Ownership is transferred
     */
    void attach(Control *control);

    /**
     * @brief Dispatch to controls, then this widget.
     */
    DispatchResult broadcast(DispatcherCtx ctx, Event *e);
};

/**
 * @brief Widget with a scrollable content area and independent viewport.
 */
class ScrollableWidget : public virtual Widget {
public:
    /** Visible region in parent-local coordinates (clip for content). */
    Rect2F viewport;

    /**
     * @param contentFrame The total logical content bounds.
     * @param viewportFrame The visible region (clip) where content is shown.
     */
    ScrollableWidget(Rect2F contentFrame, Rect2F viewportFrame, Widget *, State *);

    /** @return The active viewport used for clipping. */
    Rect2F getViewport() const;

    /** @return Current scroll progress in pixels along Y. */
    float contentProgress() const;
    /**
     * @brief Update content frame while preserving current scroll offsets.
     */
    void  setFrame(Rect2F);
    /**
     * @brief Scroll vertically by @p dy, clamped to content bounds.
     */
    void  scrollY(float dy);
};
