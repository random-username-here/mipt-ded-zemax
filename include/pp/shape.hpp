#ifndef I_PP_SHAPE
#define I_PP_SHAPE
#include "dr4/event.hpp"
#include "dr4/texture.hpp"

namespace pp {

/** 
 * @brief A shape, drawn on the canvas.
 *
 * Shapes are responsible for their editing, so things like
 * resizing a rectange or dragging it are to be implemented here.
 *
 * Shapes are created using `Tool`-s.
 *
 * Shape usually will become selected after `OnMouseDown` returned
 * true, but this is not the only way.
 *
 * Position, inherited as `Drawable` is probbably only for internal use,
 * because dragging probbably should be inside the implementation
 * (because everything else is there).
 *
 * Keyboard events may be implemented if they are needed.
 */
class Shape : public dr4::Drawable  {
public:

    virtual ~Shape() = default;

    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) { return false; };
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) { return false; };
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) { return false; };

    virtual void OnSelect() {};
    virtual void OnDeselect() {};

    virtual void DrawOn(dr4::Texture &tex) const {};
};

};

#endif
