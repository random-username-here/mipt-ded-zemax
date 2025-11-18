#ifndef I_PP_TOOL
#define I_PP_TOOL

#include <string_view>
#include <dr4/event.hpp>

namespace pp {

/**
 * @brief A tool is a thing which constructs new shapes.
 *
 * Multiple tools can construct the same kind of shape, or one
 * shape can be constructed by multiple diffrent tools in diffrent
 * ways.
 *
 * If ESC key is pressed while currently drawing something,
 * `OnBreak()` is called. If we are not drawing something,
 * then the system probbably will switch back to default tool,
 * (select tool or something like that), calling `OnEnd()`.
 * 
 */
class Tool {
public:

    /** Icon as one character, from NERDFonts */
    virtual std::string_view Icon() const = 0;
    /** Tool name to be used if icons are not supported/in tooltips */
    virtual std::string_view Name() const = 0;
    /** If we are constructing some shape or doing nothing */
    virtual bool IsCurrentlyDrawing() const = 0;

    /** This tool was selected */
    virtual void OnStart() = 0;
    /** ESC key was pressed during construction. */
    virtual void OnBreak() = 0;
    /** Tool was deselected */
    virtual void OnEnd() = 0;
    virtual bool OnMouseDown(const dr4::Event::MouseButton &evt) = 0;
    virtual bool OnMouseUp(const dr4::Event::MouseButton &evt) = 0;
    virtual bool OnMouseMove(const dr4::Event::MouseMove &evt) = 0;
    
};

};

#endif
