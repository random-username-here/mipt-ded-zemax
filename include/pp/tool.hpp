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
    virtual std::string_view Icon() const { return "?"; };
    /** Tool name to be used if icons are not supported/in tooltips */
    virtual std::string_view Name() const { return "Unnamed tool"; };
    /** If we are constructing some shape or doing nothing */
    virtual bool IsCurrentlyDrawing() const { return false; };

    /** This tool was selected */
    virtual void OnStart() {};
    /** ESC key was pressed during construction. */
    virtual void OnBreak() {};
    /** Tool was deselected */
    virtual void OnEnd() {};

    virtual bool OnMouseDown(const dr4::Event::MouseButton &) { return false; }
    virtual bool OnMouseUp(const dr4::Event::MouseButton &) { return false; }
    virtual bool OnMouseMove(const dr4::Event::MouseMove &) { return false; }
    
};

};

#endif
