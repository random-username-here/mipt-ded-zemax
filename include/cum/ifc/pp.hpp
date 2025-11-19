#ifndef I_PP_IFC
#define I_PP_IFC

#include "cum/plugin.hpp"
#include "pp/canvas.hpp"
#include "pp/tool.hpp"
#include <memory>

namespace pp {

/**
 * @brief Plugin which provides tools for screenshotter.
 */
class PPToolPlugin: public cum::Plugin {

public:
	
    inline virtual ~PPToolPlugin() {};

    /** Create tools which will draw on given canvas */
    virtual std::vector<std::unique_ptr<pp::Tool>> CreateTools(Canvas *cvs);

};

}; // namespace hui

#endif
