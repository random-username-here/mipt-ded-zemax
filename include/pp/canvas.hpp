#ifndef I_PP_CANVAS
#define I_PP_CANVAS

#include "dr4/math/color.hpp"
#include "dr4/window.hpp"
#include "pp/shape.hpp"
#include "pp/tool.hpp"

namespace pp {

/**
 * @brief A color theme for things like selection borders.
 *
 * Taking all colors from this is not mandatory, but it
 * will be nice to have a color palette at least somewhat
 * fitting into the overall theme.
 */
struct ControlsTheme {
    dr4::Color shapeColor;  ///< Default color for shapes
    dr4::Color lineColor;   ///< Color of selection borders, etc.
    dr4::Color textColor;   ///< Color for text without background
    float baseFontSize;     ///< Size of the font to use for normal tex
    dr4::Color handleColor; ///< Color for things like corner dots,
                            ///< by which rectangles are resized.
};

struct State {
    Shape* selectedShape;
    Tool* selectedTool;
};

/** A place to add shapes to */
class Canvas {
public:
    virtual ControlsTheme GetControlsTheme() const = 0;
    virtual State* GetState() const = 0;
    virtual void AddShape(Shape *shape) = 0;
    virtual void DelShape(Shape *shape) = 0;
    virtual void ShapeChanged(Shape *shape) = 0;
    virtual dr4::Window *GetWindow() = 0;
};

};

#endif // I_PP_CANVAS
