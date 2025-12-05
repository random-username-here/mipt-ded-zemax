#ifndef I_PP_CANVAS
#define I_PP_CANVAS

#include "dr4/math/color.hpp"
#include "dr4/window.hpp"
#include "pp/shape.hpp"

namespace pp {

/**
 * @brief A color theme for things like selection borders.
 *
 * Taking all colors from this is not mandatory, but it
 * will be nice to have a color palette at least somewhat
 * fitting into the overall theme.
 */
struct ControlsTheme {
    dr4::Color shapeFillColor;          ///< Default fill color for shapes
    dr4::Color shapeBorderColor;        ///< Default border color for shapes
    dr4::Color selectColor;             ///< Color of selection borders, etc.
    dr4::Color textColor;               ///< Color for text without background
    float baseFontSize;                 ///< Size of the font to use for normal text
    dr4::Color handleColor;             ///< Color for things like corner dots,
                                        ///< by which rectangles are resized.
    dr4::Color handleHoverColor;
    dr4::Color handleActiveColor;
};

/**
 * @brief A place to add shapes to.
 */
class Canvas {
public:
    virtual ControlsTheme GetControlsTheme() const = 0;
    virtual void AddShape(Shape *shape) = 0;
    virtual void DelShape(Shape *shape) = 0;
    virtual void SetSelectedShape(Shape *shape) = 0; // nullptr to deselect
    virtual Shape *GetSelectedShape() const = 0;
    virtual void ShapeChanged(Shape *shape) = 0;
    virtual dr4::Window *GetWindow() = 0;
};

};

#endif // I_PP_CANVAS
